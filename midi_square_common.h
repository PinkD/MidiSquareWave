#ifndef MIDISQUAREWAVE_MIDI_SQUARE_COMMON_H
#define MIDISQUAREWAVE_MIDI_SQUARE_COMMON_H

#include <midi_common.h>
#include "base_def.h"

typedef struct {
    Note *start;
    Note *end;
    uint32 offset;
} NoteNode;

typedef struct _NoteLinkList {
    uint32 offset;
    Note *note;
    struct _NoteLinkList *next;
} NoteLinkList;


NoteLinkList *init_note_link_list();

/**
 * find the start note of a end note and return it, need to be free
 * @param list
 * @param endNote
 * @return startNote matches endNote, NULL if not found
 */
NoteLinkList *match_and_remove_note(NoteLinkList *list, Note *endNote);

/**
 * insert a start note
 * @param list
 * @param note
 */
void insert_note(NoteLinkList *list, Note *note, uint32 offset);



const double NOTE_FREQUENCY_MAP[0x80];

#endif
