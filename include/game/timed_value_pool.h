#ifndef GAME_TIMED_VALUE_POOL_H
#define GAME_TIMED_VALUE_POOL_H
#include "ps2/prelude.h"

/* Native pool prefix. Values travel as full EE quadwords; a negative remaining
 * time marks a free entry. The caller must provide capacity before inserting. */
typedef struct {
    u128 value;
    f32 unk_10; // Sort key; the wider semantic meaning is UNVERIFIED.
    f32 remaining;
    u8 unk_18[8];
} Recovered_TimedValueEntry;

typedef struct {
    u8 unk_00[0x18];
    s16 adjustment;
    u16 unk_1A;
    s32 (*call)(void*); // UNVERIFIED: original result contract; this caller ignores it.
} Recovered_TimedValueActionMethods;

typedef struct {
    Recovered_TimedValueActionMethods* methods;
} Recovered_TimedValueAction;

typedef struct {
    Recovered_TimedValueEntry entries[128];
    s16 count;
    u8 unk_1002[2];
    Recovered_TimedValueEntry* active[128];
    Recovered_TimedValueAction* actions[4];
    u32 unk_1214;
    s16 unk_1218;
} Recovered_TimedValuePool;

typedef char TimedValueEntryStride[sizeof(Recovered_TimedValueEntry) == 32 ? 1 : -1];
typedef char TimedValuePoolActive[(u32) & ((Recovered_TimedValuePool*)0)->active == 0x1004 ? 1 : -1];
typedef char TimedValuePoolActions[(u32) & ((Recovered_TimedValuePool*)0)->actions == 0x1204 ? 1 : -1];

void TimedValuePool_Initialize(Recovered_TimedValuePool* self);
s32 TimedValuePool_SetActions(Recovered_TimedValuePool* self, Recovered_TimedValueAction** actions, u16 count, u32 value);
void TimedValuePool_Sort(Recovered_TimedValuePool* self);
s32 TimedValuePool_Reset(Recovered_TimedValuePool* self);
s32 TimedValuePool_Add(Recovered_TimedValuePool* self, u128 value, f32 duration);
void TimedValuePool_Clear(Recovered_TimedValuePool* self);
#endif
