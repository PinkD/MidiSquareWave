#ifndef MIDISQUAREWAVE_MIDI_PRE_PROCESS_H
#define MIDISQUAREWAVE_MIDI_PRE_PROCESS_H

#include <midi_common.h>

/**
 * match note by note and velocity and track
 * @param startNote start note
 * @param endNote end note
 * @return 1 on true, 0 on false
 */
int match_note(Note *startNote, Note *endNote);

/**
 * find next note track (include current track)
 * @param track start track
 * @return NULL on fail
 */
MidiTrack *find_next_note_track(MidiTrack *track);

/**
 * find the first note track of the midi
 * @param midi
 * @return NULL on fail
 */
MidiTrack *find_first_note_track(Midi *midi);

#endif
