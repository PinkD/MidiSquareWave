#include <malloc.h>
#include <wave_common.h>
#include <midi_common.h>
#include <memory.h>
#include "midi_square_core.h"


WaveData *generate_wave_from_note(double divisionTime, NoteLinkList *startNode, uint32 offset) {
    return generate_wave_from_note_with_fmt_header(divisionTime, build_default_header(), startNode, offset);
}

WaveData *generate_wave_from_note_with_fmt_header(double divisionTime, FmtHeader *fmt, NoteLinkList *startNode, uint32 offset) {
    WaveData *waveData = calloc(sizeof(WaveData), 1);

    offset = offset - startNode->offset;

    double freq = NOTE_FREQUENCY_MAP[startNode->note->note];

    //step for 4/4 is 1/4 note
    //TODO: support other steps

    uint32 noteRealTime = division_to_real_time(offset, divisionTime, fmt->byte_rate);
    //cycle, 4 means quarter note
    uint32 cycle = (uint32) (1 / freq * fmt->byte_rate / 4);

    waveData->data_size = noteRealTime;

    byte *data = calloc(waveData->data_size, 1);
    offset = 0;
    uint16 scale = 0xffff;
    const byte MAX_VEL = 0xff;

    while (offset < noteRealTime - cycle) {
        int16 scaledVelocity = startNode->note->velocity * scale / MAX_VEL;
        write_note_to_wave(data + offset, scaledVelocity, cycle);
        offset += cycle;
    }

    waveData->data = data;
    return waveData;

}

void write_note_to_wave(byte *data, int16 velocity, uint32 count) {
    int16 *p = (int16 *) data;
    for (int i = 0; i < count / 4; i++) {
        p[i] = velocity;
        p[count / 4 + i] = -velocity;
    }
}


WaveData *generate_empty_wave_by_offset_with_header(FmtHeader *header, double divisionTime, uint32 offset) {
    WaveData *waveData = calloc(sizeof(WaveData), 1);
    double noteRealTime = (double) offset / divisionTime;
    waveData->data_size = (uint32) (noteRealTime * header->byte_rate);
    waveData->data = calloc(waveData->data_size, 1);
    return waveData;
}

WaveData *generate_empty_wave_by_offset(double divisionTime, uint32 offset) {
    return generate_empty_wave_by_offset_with_header(build_default_header(), divisionTime, offset);
}

uint32 division_to_real_time(uint32 offset, double divisionTime, uint32 byte_rate) {
    return (uint32) ((double) offset / divisionTime * byte_rate);
}

static FmtHeader *p = NULL;

FmtHeader *build_default_header() {
    if (!p) {
        static FmtHeader header;
        header.sample_rate = 44100;
        header.bits_per_sample = 16;
        header.channel = 2;
        header.byte_rate = header.sample_rate * header.bits_per_sample * header.channel / 8;
        p = &header;
    }
    return p;
}

