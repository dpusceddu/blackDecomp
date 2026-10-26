#ifndef GAME_ACTOR_RECORDS_H
#define GAME_ACTOR_RECORDS_H
#include "ps2/prelude.h"

/* Partial PS2 record layout. The meanings of the two queried byte flags remain
 * unknown; the record stride and current-record index are shared by this TU. */
typedef struct {
    s32 id;
    u8 unk_04;
    u8 unk_05; // UNVERIFIED: getter remains a draft.
    u8 unk_06; // UNVERIFIED: getter remains a draft.
    u8 unk_07[9];
    f32 startTime;
    u8 unk_14[0x4C];
} Recovered_ActorRecord;

typedef struct {
    Recovered_ActorRecord records[3];
    s32 current;
    u8 unk_124[0xC];
    void* owner;
} Recovered_ActorRecords;

typedef char ActorRecordStride[sizeof(Recovered_ActorRecord) == 0x60 ? 1 : -1];
typedef char ActorRecordIndexOffset[(u32)&((Recovered_ActorRecords*)0)->current == 0x120 ? 1 : -1];
typedef char ActorRecordOwnerOffset[(u32)&((Recovered_ActorRecords*)0)->owner == 0x130 ? 1 : -1];
s32 func_001891C0(Recovered_ActorRecords* self);
s32 func_00189208(Recovered_ActorRecords* self);
s32 func_00189250(Recovered_ActorRecords* self, s32 id);
/* The current object's native kind predicate accepts 0 and 3. */
u8 ActorRecords_CurrentKindAllowed(Recovered_ActorRecords* self);
f32 ActorRecords_ElapsedTime(Recovered_ActorRecords* self);

#endif
