#include <libzvbi.h>
#include <malloc.h>
#include "midi_square_common.h"
#include "midi_pre_process.h"

NoteLinkList *match_and_remove_note(NoteLinkList *list, Note *endNote) {
    NoteLinkList *last;
    NoteLinkList *noteNode;
    last = list;
    noteNode = list->next;//list head is empty
    while (noteNode) {
        if (match_note(noteNode->note, endNote)) {
            last->next = noteNode->next;
            return noteNode;
        }
        last = noteNode;
        noteNode = noteNode->next;
    }
    return NULL;
}

NoteLinkList *init_note_link_list() {
    NoteLinkList *node = calloc(sizeof(NoteLinkList), 1);
    return node;
}

void insert_note(NoteLinkList *list, Note *note, uint32 offset) {
    NoteLinkList *node = malloc(sizeof(NoteLinkList));
    node->note = note;
    node->offset = offset;
    node->next = NULL;
    while (list->next) {
        list = list->next;
    }
    list->next = node;
}

const double NOTE_FREQUENCY_MAP[] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        27.50000000,
        29.13523509,
        30.86770633,
        32.70319566,
        34.64782887,
        36.70809599,
        38.89087297,
        41.20344461,
        43.65352893,
        46.24930284,
        48.99942950,
        51.91308720,
        55,
        58.27047019,
        61.73541266,
        65.40639133,
        69.29565774,
        73.41619198,
        77.78174593,
        82.40688923,
        87.30705786,
        92.49860568,
        97.99885900,
        103.82617439,
        110,
        116.54094038,
        123.47082531,
        130.81278265,
        138.59131549,
        146.83238396,
        155.56349186,
        164.81377846,
        174.61411572,
        184.99721136,
        195.99771799,
        207.65234879,
        220,
        233.08188076,
        246.94165063,
        261.62556530,
        277.18263098,
        293.66476792,
        311.12698372,
        329.62755691,
        349.22823143,
        369.99442271,
        391.99543598,
        415.30469758,
        440,
        466.16376152,
        493.88330126,
        523.25113060,
        554.36526195,
        587.32953583,
        622.25396744,
        659.25511383,
        698.45646287,
        739.98884542,
        783.99087196,
        830.60939516,
        880,
        932.32752304,
        987.76660251,
        1046.50226120,
        1108.73052391,
        1174.65907167,
        1244.50793489,
        1318.51022765,
        1396.91292573,
        1479.97769085,
        1567.98174393,
        1661.21879032,
        1760,
        1864.65504607,
        1975.53320502,
        2093.00452240,
        2217.46104781,
        2349.31814334,
        2489.01586978,
        2637.02045530,
        2793.82585146,
        2959.95538169,
        3135.96348785,
        3322.43758064,
        3520,
        3729.31009214,
        3951.06641005,
        4186.00904481,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
};
