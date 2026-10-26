#ifndef GAME_SEQUENCE_H
#define GAME_SEQUENCE_H
#include "ps2/prelude.h"

/* Partial PS2 views shared by the sequence variants. Unknown bytes retain
 * their native offsets; these views do not establish the original class names. */
typedef struct {
    u16* indices;
    u8 count;
    u8 unk_05[3];
} Recovered_SequenceEntry;

typedef struct {
    u8 unk_00[0x14];
    Recovered_SequenceEntry* entries;
} Recovered_SequenceTable;

typedef struct {
    u8 unk_00[0x30];
    void* unk_30;
    u8 unk_34[0x2C];
} Recovered_SequenceSlot;

typedef struct {
    u8 unk_00[0x18];
    Recovered_SequenceTable* table;
    u8 unk_1C[0xC];
    s8* order;
    u8 unk_2C[0x64];
    void* active;
    void* definition;
    s32 slotCount;
    Recovered_SequenceSlot* slots;
} Recovered_SequenceState;

typedef struct {
    s16 adjustment;
    u16 unk_02;
    void (*call)(void*, void*);
} Recovered_SequenceVirtual;

typedef char SequenceEntryStride[sizeof(Recovered_SequenceEntry) == 8 ? 1 : -1];
typedef char SequenceSlotStride[sizeof(Recovered_SequenceSlot) == 0x60 ? 1 : -1];
typedef char SequenceActiveOffset[(u32)&((Recovered_SequenceState*)0)->active == 0x90 ? 1 : -1];
typedef char SequenceSlotsOffset[(u32)&((Recovered_SequenceState*)0)->slots == 0x9C ? 1 : -1];

s32 Sequence_ClassifyStorage(void* address);
void Sequence_RemoveActor(void* self, void* actor);
void Sequence_ShuffleIndices(void* self, s8* order, s32 count);
s32 Sequence_InitializeSlots(Recovered_SequenceState* self, s64 owner, void* definition, s32 table);

#endif
