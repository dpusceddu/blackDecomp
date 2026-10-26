#ifndef GAME_AI_PRIORITY_QUEUE_H
#define GAME_AI_PRIORITY_QUEUE_H

#include "ps2/prelude.h"

/* Partial PS2 queue view; insert and selection confirm the accessed fields.
 * The score callback receives the table-adjusted queue address. */
typedef struct {
    void* object;
    f32 score;
    u8 used;
    u8 tag;
    u8 unk_0A[2];
} Recovered_PriorityEntry;

typedef struct {
    u8 unk_00[8];
    s16 adjustment;
    u16 unk_0A;
    f32 (*score)(void*, void*);
} Recovered_PriorityQueueTable;

typedef struct {
    Recovered_PriorityEntry entries[100];
    u8 count;
    u8 unk_4B1[3];
    Recovered_PriorityQueueTable* table;
} Recovered_PriorityQueue;

typedef char PriorityEntryStride[sizeof(Recovered_PriorityEntry) == 12 ? 1 : -1];
typedef char PriorityQueueCount[(u32)&((Recovered_PriorityQueue*)0)->count == 0x4B0 ? 1 : -1];
typedef char PriorityQueueTable[(u32)&((Recovered_PriorityQueue*)0)->table == 0x4B4 ? 1 : -1];
#endif
