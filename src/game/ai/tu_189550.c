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

#ifdef NON_MATCHING
// Unmatched: scalar/vector temporary allocation and branch scheduling differ (53 instructions).
#include "game/actor_slots.h"
#include "ps2/vu0_lowering.h"

extern Recovered_AIManager* D_0040F4D4;
extern void* D_0040F4D0;
extern const f32 D_003F6580[];
extern const f32* func_0018E1B0(void*);
extern void* func_00135550(void*);
extern s32 func_00188F10(Recovered_ActorRecords*);
extern s32 func_00188F58(Recovered_ActorRecords*);
extern s128 func_00189070(Recovered_ActorRecords*, Recovered_ActorRecord*);
extern s128 func_0018D918(void*);
extern s32 func_0018DDD8(void*);
extern s32 func_00173370(void*, s32, void*);
extern s32 func_00178F18(Recovered_ActorSlot*);
extern f32 func_0018E210(void*, void*);

static inline s32 ActorPriorityIsOld(f32 value) { return value > 0.5f; }
static inline u8 ActorPriorityIsTiny(f32 value) { return value < 2.3283064e-10f; }

void func_00189C10(Recovered_ActorRecords* self, Recovered_ActorRecord* record) {
    f32 weight, amount;
    s32 state, filter;
    f32 score = 0.0f;
    const f32* weights = func_0018E1B0((u8*)self->owner + 0xC94);
    s32 old = 0;
    if (record->id == -1) {
        weight = weights[0];
        record->priority = weight;
        return;
    }
    if (record->bias > 0.0f) {
        weight = weights[1];
        amount = (__ee_min_s(__ee_max_s(record->bias / 100.0f, 0.0f), 1.0f) * 0.7f) + 0.3f;
        score = amount * weight + 0.0f;
    }
    if (record->unk_06) {
        weight = weights[2];
        score += weight;
    }
    if (record->unk_05) {
        weight = weights[3];
        amount = ((1.0f -
                   __ee_min_s(__ee_max_s((M2C_FIELD(D_0040F4D0, f32*, 0x20) - record->startTime) / 5.0f, 0.0f), 1.0f)) *
                  0.7f) +
                 0.3f;
        score += amount * weight;
    }
    weight = weights[10];
    if (weight != 0.0f) {
        f32 age = M2C_FIELD(D_0040F4D0, f32*, 0x20) - record->unk_1C;
        old = ActorPriorityIsOld(age);
        if (old) score += weight * __ee_min_s(__ee_max_s((age - 0.5f) * 0.5f, 0.0f), 1.0f);
    }
    amount = 1.0f - __ee_min_s(__ee_max_s(record->selectionMetric / 30.0f, 0.0f), 1.0f);
    if (old)
        weight = weights[5];
    else
        weight = weights[4];
    score += weight * amount;
    state = ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id)->state;
    weight = D_003F6580[state];
    score += weight;
    if (state == 0) {
        Recovered_ManagedActor* actor;
        actor = ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id)->actor;
        weight = weights[7];
        if (weight != 0.0f && M2C_FIELD(func_00135550(actor), s32*, 0x80) == 1) {
            Recovered_ActorRecords* records = (Recovered_ActorRecords*)((u8*)func_00135550(actor) + 0x150);
            if (func_00188F10(records) &&
                func_00188F58(records) == M2C_FIELD(M2C_FIELD(self->owner, void**, 0x7C), s32*, 0x380))
                score += weight;
        }
    }
    weight = weights[8];
    if (weight != 0.0f) {
        BkVuVector target = func_00189070(self, record);
        BkVuVector one = BkVuOneX();
        BkVuVector position = M2C_FIELD(M2C_FIELD(self->owner, void**, 0x7C), s128*, 0xA0);
        BkVuVector delta = BkVuSubXYZ(target, position);
        BkVuVector squared = BkVuMulXYZ(delta, delta);
        BkVuVector sum = BkVuLowerSumXYZ(squared, squared, one);
        f32 factor;
        u8 tiny = ActorPriorityIsTiny(__ee_vu_read_x(sum));
        if (tiny)
            factor = 1.0f;
        else {
            BkVuVector direction, forward, product;
            squared = BkVuLowerMulXYZ(sum, delta, delta);
            direction = BkVuNormalizeXYZ(delta, BkVuLowerSumXYZ(squared, squared, one));
            forward = func_0018D918((u8*)self->owner + 0xD10);
            product = BkVuMulXYZ(forward, direction);
            factor = __ee_min_s(
                __ee_max_s(__ee_vu_read_x(BkVuLowerSumXYZ(product, product, BkVuLowerOneX(forward))), 0.0f), 1.0f);
        }
        score += weight * factor;
    }
    weight = weights[9];
    if (weight != 0.0f && func_0018DDD8((u8*)self->owner + 0xC94) &&
        func_00173370((u8*)D_0040F4D4 + 0x22800, record->id, M2C_FIELD(self->owner, void**, 0x7C)))
        score += weight;
    weight = weights[11];
    if (weight != 0.0f && record->id == func_00188F58(self)) score += weight;
    weight = weights[12];
    if (weight != 0.0f &&
        func_00178F18(ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id))) {
        void* policy = (u8*)self->owner + 0xC94;
        score += weight *
                 func_0018E210(
                     policy,
                     ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id)->actor);
    }
    filter = self->categoryFilter;
    switch (filter) {
        case 0:
        case 1:
        case 2: break;
        case 3:
            if (ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id)->state == 2)
                score += 100000.0f;
            break;
        default: break;
    }
    record->priority = score;
}

#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_189550", func_00189C10);
#endif

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
