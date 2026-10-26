#ifndef GAME_TIMED_FLAG_QUEUE_H
#define GAME_TIMED_FLAG_QUEUE_H
#include "ps2/prelude.h"

/* Partial item view. The expiration helper compares +0x10 with the frame clock;
 * the original class identity is unknown. */
typedef struct {
    u8 unk_00[0x10];
    f32 expiresAt;
    u8 unk_14[8];
    u32 previousFlags;
} Recovered_TimedFlagItem;

typedef struct {
    Recovered_TimedFlagItem* item;
    u32 flags;
} Recovered_TimedFlagEntry;

typedef struct {
    Recovered_TimedFlagEntry entries[300];
    s32 head;
    s32 tail;
    s32 count;
} Recovered_TimedFlagQueue;

typedef char TimedFlagEntryStride[sizeof(Recovered_TimedFlagEntry) == 8 ? 1 : -1];
typedef char TimedFlagQueueHead[(u32) & ((Recovered_TimedFlagQueue*)0)->head == 0x960 ? 1 : -1];
typedef char TimedFlagQueueCount[(u32) & ((Recovered_TimedFlagQueue*)0)->count == 0x968 ? 1 : -1];

void* TimedFlagQueue_Reset(Recovered_TimedFlagQueue* self);
s32 TimedFlagQueue_AddFlags(Recovered_TimedFlagQueue* self, Recovered_TimedFlagItem* item, u32 flags);
Recovered_TimedFlagEntry* TimedFlagQueue_Insert(Recovered_TimedFlagQueue* self, Recovered_TimedFlagItem* item);
Recovered_TimedFlagEntry* TimedFlagQueue_Pop(Recovered_TimedFlagQueue* self);
Recovered_TimedFlagEntry* TimedFlagQueue_Find(Recovered_TimedFlagQueue* self, Recovered_TimedFlagItem* item);
Recovered_TimedFlagEntry* TimedFlagQueue_Peek(Recovered_TimedFlagQueue* self);
s32 TimedFlagQueue_IsFull(Recovered_TimedFlagQueue* self);
s32 TimedFlagQueue_IsEmpty(Recovered_TimedFlagQueue* self);
void TimedFlagItem_ClearPreviousFlags(Recovered_TimedFlagItem* item);
s32 TimedFlagItem_HasExpired(Recovered_TimedFlagItem* item);
#endif
