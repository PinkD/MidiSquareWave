#include "midi_pre_process.h"

#include <stdio.h>

MidiTrack *find_next_note_track(MidiTrack *track) {
    while (track) {
        TrackEvent *trackEvent = track->trackEvent;
        while (trackEvent) {
            if (trackEvent->type == TRACK_EVENT_TYPE_NOTE) {
                return track;
            }
            trackEvent = trackEvent->next;
        }
        track = track->next;
    }
    return NULL;
}

MidiTrack *find_first_note_track(Midi *midi) {
    MidiTrack *track = midi->track;
    return find_next_note_track(track);
}

int match_note(Note *startNote, Note *endNote) {
    const int true = 1;
    const int false = 0;
    if (startNote && endNote && startNote->type == NOTE_START && endNote->type == NOTE_END) {
        if (startNote->note == endNote->note && startNote->track == endNote->track) {
            return true;
        }
    }
    return false;
}
