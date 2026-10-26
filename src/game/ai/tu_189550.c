#include "include_asm.h"
#include "game/actor_slots.h"
#include "ps2/vu0_lowering.h"

extern Recovered_AIManager* D_0040F4D4;
extern void* D_0040F4D0;
extern s32 func_00189740(Recovered_ActorRecords*, Recovered_ManagedActor*, s32);
extern s32 func_001897E8(Recovered_ActorRecords*, s32, s32);
extern void func_00189B28(Recovered_ActorRecords*, Recovered_ActorRecord*);
extern s32 func_00189B90(Recovered_ActorRecords*, s32);
extern const s128* func_00178D30(Recovered_ActorSlot*);
extern void func_0018A2C8(Recovered_ActorRecords*, Recovered_ActorRecord*);
extern s32 func_00181AD0(void*, s32);
extern s128 func_00189070(Recovered_ActorRecords*, Recovered_ActorRecord*);
extern s32 func_0018D768(void*, s32);
extern void func_0018A1C0(Recovered_ActorRecords*, Recovered_ActorRecord*);
extern void func_0018A238(Recovered_ActorRecords*, Recovered_ActorRecord*);
extern void func_00189C10(Recovered_ActorRecords*, Recovered_ActorRecord*);
extern f32 func_0018DD88(void*);
extern void func_0018A9C8(Recovered_ActorRecords*, Recovered_ManagedActor*, Recovered_ManagedSlot*);
extern void func_00173640(f32*, f32);
extern void func_00173690(f32*);
extern void func_00188A40(void*, s32);

void func_00189550(Recovered_ActorRecords* self, Recovered_ManagedActor* actor, f32 amount) {
    s32 index = func_00189740(self, actor, 0);
    if (index != -1) self->records[index].bias += amount;
}

s32 func_001895A8(Recovered_ActorRecords* self, Recovered_ManagedActor* actor) {
    return func_00189740(self, actor, 1);
}

void func_001895C8(Recovered_ActorRecords* self, Recovered_ManagedSlot* peer, Recovered_ManagedActor* actor) {
    BkVuVector one = BkVuOneX();
    BkVuVector delta =
        BkVuSubXYZ(actor->transform.position, ((Recovered_ManagedSlot*)self->owner)->actor->transform.position);
    f32 squared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one));
    f32 radiusSquared = func_0018DD88((u8*)self->owner + 0xC94);
    radiusSquared *= func_0018DD88((u8*)self->owner + 0xC94);
    if (squared < radiusSquared) func_0018A9C8(self, actor, peer);
    else {
        delta =
            BkVuSubXYZ(peer->actor->transform.position, ((Recovered_ManagedSlot*)self->owner)->actor->transform.position);
        squared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one));
        if (squared < 400.0f) func_0018A9C8(self, actor, peer);
    }
}

s32 func_001896E0(Recovered_ActorRecords* self, Recovered_ManagedActor* actor) {
    return func_00189740(self, actor, 0);
}

s32 func_00189700(Recovered_ActorRecords* self, Recovered_ManagedActor* actor) {
    return func_00189740(self, actor, 1);
}

s32 func_00189720(Recovered_ActorRecords* self, Recovered_ManagedActor* actor) {
    return func_00189B90(self, actor->recordId);
}

#ifdef NON_MATCHING
// Unmatched: category-2 branch has an extra load-delay nop.
s32 func_00189740(Recovered_ActorRecords* self, Recovered_ManagedActor* actor, s32 force) {
    if (actor->invalid) return -1;
    switch (self->categoryFilter) {
    case 0:
        break;
    case 1:
        if (actor->unk_C4 != 2) return -1;
        break;
    case 2:
        if (actor->unk_C4 == 2) return -1;
        break;
    }
    return func_001897E8(
        self, ActorSlotTable_FindState0Actor((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), actor), force);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_189550", func_00189740);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_189550", func_001897E8);

s32 func_00189AD0(Recovered_ActorRecords* self, Recovered_ManagedActor* actor) {
    s32 id = actor->recordId;
    s32 cursor = (s32)self;
    s32 end = cursor + sizeof(self->records);
    do {
        Recovered_ActorRecord* record = (Recovered_ActorRecord*)cursor;
        if (record->id == id) {
            if (record->unk_05) func_00189B28(self, record);
            return 1;
        }
        cursor += sizeof(Recovered_ActorRecord);
    } while (cursor < end);
    return 0;
}

void func_00189B28(Recovered_ActorRecords* self, Recovered_ActorRecord* record) {
    Recovered_ActorSlot* entry =
        ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id);
    record->unk_05 = 1;
    record->position = *func_00178D30(entry);
    record->unk_30 = ((Recovered_ManagedSlot*)self->owner)->actor->transform.position;
}

s32 func_00189B90(Recovered_ActorRecords* self, s32 id) {
    s32 more;
    s32 cursor = (s32)self;
    s32 end = cursor + sizeof(self->records);
search_record:
    if (((Recovered_ActorRecord*)cursor)->id != id) {
        cursor += sizeof(Recovered_ActorRecord);
        more = cursor < end;
        if (!more) return more;
        goto search_record;
    }
    func_0018A2C8(self, (Recovered_ActorRecord*)cursor);
    return func_00181AD0((u8*)self->owner + 0xEC0, 3);
}

s32 func_00189BF8(Recovered_ActorRecords* self, s32 id) {
    return (self->actorMask & (1U << id)) != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_189550", func_00189C10);

void func_0018A118(Recovered_ActorRecords* self, Recovered_ActorRecord* record) {
    if (record->id != -1) {
        if (record->unk_06) {
            record->startTime = M2C_FIELD(D_0040F4D0, f32*, 0x20);
            record->position = func_00189070(self, record);
            record->unk_05 = 1;
        }
        if (func_0018D768((u8*)self->owner + 0xD10, record->id)) {
            record->unk_1C = M2C_FIELD(D_0040F4D0, f32*, 0x20);
        }
        func_0018A1C0(self, record);
        func_0018A238(self, record);
    }
    func_00189C10(self, record);
}

/* The level's gameplay role is unknown; the native flag selects its rise or decay. */
void func_0018A1C0(Recovered_ActorRecords* self, Recovered_ActorRecord* record) {
    if (record->unk_06) record->level += M2C_FIELD(D_0040F4D0, f32*, 0x1C) / 3.0f;
    else record->level -= M2C_FIELD(D_0040F4D0, f32*, 0x1C) * 0.25f;
    record->level = __ee_min_s(__ee_max_s(record->level, 0.0f), 1.0f);
}

void func_0018A238(Recovered_ActorRecords* self, Recovered_ActorRecord* record) {
    if (record->unk_06) {
        BkVuVector position = record->position;
        BkVuVector one = BkVuOneX();
        BkVuVector delta = BkVuSubXYZ(record->unk_40, position);
        f32 squared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one));
        if (squared > 9.0f) {
            record->unk_40 = position;
            func_00173640(&record->unk_50, 1.0f);
        }
    } else {
        record->unk_40 = record->position;
        func_00173640(&record->unk_50, 1.0f);
    }
}

#ifdef NON_MATCHING
/* Native reset clears XYZ; the stored W lane has no established meaning. */
static inline BkVuVector RecordZeroXYZ(void) {
    BkVuVector value;
    __asm__("vadd.xyz valuev, vf0, vf0" : "=j valuev"(value));
    return value;
}
// Unmatched: native vector construction retains a stack temporary and different store scheduling.
void func_0018A2C8(Recovered_ActorRecords* self, Recovered_ActorRecord* record) {
    BkVuVector zero = RecordZeroXYZ();
    self->actorMask &= ~(1U << record->id);
    record->id = -1;
    record->unk_05 = 0;
    record->unk_06 = 0;
    record->unk_07 = 0;
    record->unk_1C = -1.0f;
    record->unk_40 = zero;
    record->priority = -1.0f;
    record->startTime = -1.0f;
    record->position = zero;
    record->unk_30 = zero;
    func_00173690(&record->unk_50);
    if (record->unk_04 == self->current) {
        self->current = -1;
        func_00188A40((u8*)self->owner + 0x290, -1);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_189550", func_0018A2C8);
#endif
