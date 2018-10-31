#include <midi_reader.h>

#include <log.h>
#include <malloc.h>
#include <wave_common.h>
#include <memory.h>
#include <wave_writer.h>
#include "midi_pre_process.h"
#include "midi_square_common.h"
#include "midi_square_core.h"

WaveHeader *make_wave_header_without_size();

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("%s in.mid out.wav\n", argv[0]);
        return 0;
    }

    Midi *midi = read_midi_file(argv[1]);

    if (!midi) {
        return -1;
    }

    MidiTrack *noteTrack = find_first_note_track(midi);


    uint32 trackTime = get_midi_track_time(noteTrack);

    uint32 offset = 0;

    TrackEvent *trackEvent = noteTrack->trackEvent;

    NoteLinkList *list = init_note_link_list();

    Wave *wave = malloc(sizeof(Wave));
    wave->data = malloc(sizeof(WaveData));

    memcpy(wave->data->data_chunk_header, "data", 4);

    wave->header = make_wave_header_without_size();

    double divisionTime = get_division_time(midi);

    double trackRealTime = (double) trackTime / divisionTime;

    uint32 byte_rate = wave->header->fmt.byte_rate;

    wave->data->data_size = (uint32) (byte_rate * trackRealTime);
    if (wave->data->data_size % 4) {
        wave->data->data_size += (4 - wave->data->data_size % 4);
    }
    wave->data->data = malloc(wave->data->data_size);

    int start = 0;

    while (trackEvent) {
        if (trackEvent->type == TRACK_EVENT_TYPE_NOTE) {
            NoteEvent *noteEvent = (NoteEvent *) trackEvent->event;
            if (noteEvent->note->type == NOTE_START) {
                insert_note(list, noteEvent->note, offset + trackEvent->offset);
                if (trackEvent->offset) {
                    WaveData *waveData = generate_empty_wave_by_offset_with_header(&wave->header->fmt, divisionTime, trackEvent->offset);
                    memcpy(wave->data->data + division_to_real_time(offset, divisionTime, byte_rate), waveData->data, waveData->data_size);
                    free_wave_data(waveData);
                }
                start = 1;
            } else {//NOTE_END
                NoteLinkList *startNode = match_and_remove_note(list, noteEvent->note);
                if (startNode) {
                    WaveData *waveData = generate_wave_from_note_with_fmt_header(divisionTime, &wave->header->fmt, startNode, offset + noteEvent->note->offset);
                    memcpy(wave->data->data + division_to_real_time(startNode->offset, divisionTime, byte_rate), waveData->data, waveData->data_size);
                    free_wave_data(waveData);
                    free(startNode);
                    start = 0;
                } else {
                    log_w("could not find a start note for the end note");
                }
            }
        } else {
            if (!start) {
                if (trackEvent->offset) {
                    WaveData *waveData = generate_empty_wave_by_offset_with_header(&wave->header->fmt, divisionTime, trackEvent->offset);
                    memcpy(wave->data->data + division_to_real_time(offset, divisionTime, byte_rate), waveData->data, waveData->data_size);
                    free_wave_data(waveData);
                }
            }
        }
        offset += trackEvent->offset;
        trackEvent = trackEvent->next;
    }
    write_wave(argv[2], wave);

    free_midi(midi);
    free_wave(wave);
    return 0;
}


WaveHeader *make_wave_header_without_size() {
    WaveHeader *header = malloc(sizeof(WaveHeader));
    memcpy(header->fmt.fmt, "fmt ", 4);

    header->fmt.sample_rate = 44100;
    header->fmt.bits_per_sample = 16;
    header->fmt.channel = 2;
    header->fmt.byte_rate = header->fmt.sample_rate * header->fmt.bits_per_sample * header->fmt.channel / 8;

    header->fmt.block_align = 4;
    header->fmt.format = 1;
    header->fmt.size = 16;

    memcpy(header->riff.wave, "WAVE", 4);
    memcpy(header->riff.riff, "RIFF", 4);
    header->riff.size = 44;
    return header;
}