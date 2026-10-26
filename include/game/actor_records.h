#ifndef GAME_ACTOR_RECORDS_H
#define GAME_ACTOR_RECORDS_H
#include "ps2/prelude.h"

/* Partial PS2 record layout. The meanings of the two queried byte flags remain
 * unknown; the record stride and current-record index are shared by this TU. */
typedef struct {
    s32 id;
    u8 unk_04;
    u8 unk_05;
    u8 unk_06; // UNVERIFIED: getter remains a draft.
    u8 unk_07;
    u8 unk_08[4];
    f32 priority;
    f32 startTime;
    u8 unk_14[4];
    f32 selectionMetric; // UNVERIFIED: minimum-metric selection remains a draft.
    f32 unk_1C;
    s128 position;
    s128 unk_30;
    s128 unk_40;
    f32 unk_50;
    u8 unk_54[0xC];
} Recovered_ActorRecord;

typedef struct {
    Recovered_ActorRecord records[3];
    s32 current;
    u8 unk_124[0xC];
    void* owner;
} Recovered_ActorRecords;

typedef char ActorRecordStride[sizeof(Recovered_ActorRecord) == 0x60 ? 1 : -1];
typedef char ActorRecordIndexOffset[(u32) & ((Recovered_ActorRecords*)0)->current == 0x120 ? 1 : -1];
typedef char ActorRecordOwnerOffset[(u32) & ((Recovered_ActorRecords*)0)->owner == 0x130 ? 1 : -1];
typedef char ActorRecordPositionOffset[(u32) & ((Recovered_ActorRecord*)0)->position == 0x20 ? 1 : -1];
s32 func_001891C0(Recovered_ActorRecords* self);
s32 func_00189208(Recovered_ActorRecords* self);
s32 func_00189250(Recovered_ActorRecords* self, s32 id);
/* The current object's native kind predicate accepts 0 and 3. */
u8 ActorRecords_CurrentKindAllowed(Recovered_ActorRecords* self);
f32 ActorRecords_ElapsedTime(Recovered_ActorRecords* self);

void ActorRecords_ImportEligiblePeer(Recovered_ActorRecords* self);
void* ActorRecords_CurrentOrFallback(Recovered_ActorRecords* self);
void ActorRecords_CopyPeerRecord(Recovered_ActorRecords* self, s32 id, void* peer);

#endif
