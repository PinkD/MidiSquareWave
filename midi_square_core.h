#ifndef MIDISQUAREWAVE_MIDI_SQUARE_CORE_H
#define MIDISQUAREWAVE_MIDI_SQUARE_CORE_H

#include <wave_common.h>
#include <midi_common.h>

#include "midi_square_common.h"

/**
 * call generate_wave_from_note_with_fmt_header with default header
 * @param divisionTime
 * @param startNode
 * @param offset
 * @return
 */
WaveData *generate_wave_from_note(double divisionTime, NoteLinkList *startNode, uint32 offset);

/**
 * generate wave from midi note
 * @param divisionTime division time in second
 * @param fmt fmt header, see `FmtHeader` in midi_common.h
 * @param startNode node with start note and its offset
 * @param offset offset of end note
 * @return wave data, only data and data_size is usable, need to be free
 */
WaveData *generate_wave_from_note_with_fmt_header(double divisionTime, FmtHeader *fmt, NoteLinkList *startNode, uint32 offset);

/**
 * write int16 velocity
 * OPTIONAL TODO: support 8bit or other format
 * @param data wave data with offset
 * @param velocity data to write
 * @param count data count
 */
void write_note_to_wave(byte *data, int16 velocity, uint32 count);

/**
 * generate zero velocity wave data
 * @param header same as `generate_wave_from_note
 * @param divisionTime
 * @param offset
 * @return
 */
WaveData *generate_empty_wave_by_offset_with_header(FmtHeader *header, double divisionTime, uint32 offset);

/**
 * call `generate_empty_wave_by_offset_with_header` with default header
 * @param divisionTime
 * @param offset
 * @return
 */
WaveData *generate_empty_wave_by_offset(double divisionTime, uint32 offset);

/**
 * convert a division time to real block count in wave data
 * @param offset
 * @param divisionTime
 * @param byte_rate see `FmtHeader.byte_rate`
 * @return block count for wave data
 */
uint32 division_to_real_time(uint32 offset, double divisionTime, uint32 byte_rate);

/**
 * build a default header, using static field, you don't need to free it
 * !!!NOTE: call this function carefully in multi thread application
 * @return default fmt header
 */
FmtHeader *build_default_header();

#endif
