#include "include_asm.h"
#include "game/actor_slots.h"

extern Recovered_AIManager* D_0040F4D4;
extern const s128* func_00178D30(Recovered_ActorSlot*);
extern s128 func_00178E60(Recovered_ActorSlot*);
/* The region transforms the actor's position and half-height before testing
 * its local bounds. The gameplay identity of actor category 2 is unknown. */
extern s32 func_00176310(void*, Recovered_ManagedActor*, const void*);
Recovered_ActorSlot* func_00188F80(Recovered_ActorRecords*);
s128 func_00189070(Recovered_ActorRecords*, Recovered_ActorRecord*);
s128 func_00189178(Recovered_ActorRecords*, Recovered_ActorRecord*);

#ifdef NON_MATCHING
// Unmatched: boolean normalization omits the native intermediate return-register copy.
s32 func_00188BF8(Recovered_ActorRecords* self) {
    u8 result = 0;
    if (self->current != -1) result = ActorSlot_IsState0Kind2(func_00188F80(self)) != 0;
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_188bf8", func_00188BF8);
#endif

s32 func_00188C38(Recovered_ActorRecords* self, const void* region) {
    if (region) {
        s32 cursor = (s32)self;
        s32 end = cursor + sizeof(self->records);
        do {
            Recovered_ActorRecord* record = (Recovered_ActorRecord*)cursor;
            if (record->id != -1) {
                Recovered_ActorSlot* entry = ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id);
                if (ActorSlot_IsState0(entry) && entry->actor->unk_C4 == 2 &&
                    func_00176310((u8*)D_0040F4D4 + 0xFA0, entry->actor, region)) return 1;
            }
            cursor += sizeof(Recovered_ActorRecord);
        } while (cursor < end);
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_188bf8", func_00188D08);

s32 func_00188F10(Recovered_ActorRecords* self) {
    return ~self->current != 0;
}

#ifdef NON_MATCHING
// Unmatched: loop load and branch placement differ.
s32 func_00188F20(Recovered_ActorRecords* self) {
    s32 cursor = (s32)self;
    s32 end = cursor + sizeof(self->records);
    s32 value = *(s32*)cursor;
    do {
        cursor += sizeof(Recovered_ActorRecord);
        if (value != -1) return 1;
        if (cursor >= end) break;
        value = *(s32*)cursor;
    } while (1);
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_188bf8", func_00188F20);
#endif
s32 func_00188F58(Recovered_ActorRecords* self) {
    if (self->current >= 0) return self->records[self->current].id;
    return -1;
}

Recovered_ActorSlot* func_00188F80(Recovered_ActorRecords* self) {
    return ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8),
                                   self->records[self->current].id);
}

/* Requires a valid record. Equal or unordered metrics retain the first one. */
Recovered_ActorSlot* func_00188FB8(Recovered_ActorRecords* self) {
    s32 selected = -1;
    s32 i;
    for (i = 0; i < 3; ++i) {
        if (self->records[i].id != -1) {
            if (selected == -1 || self->records[i].selectionMetric < self->records[selected].selectionMetric) {
                selected = i;
            }
        }
    }
    return ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), self->records[selected].id);
}

s128 func_00189048(Recovered_ActorRecords* self) {
    return func_00189070(self, &self->records[self->current]);
}

s128 func_00189070(Recovered_ActorRecords* self, Recovered_ActorRecord* record) {
    return *func_00178D30(ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id));
}

/* This separate quadword query has an unknown gameplay interpretation. */
s128 func_001890A8(Recovered_ActorRecords* self) {
    return func_00189178(self, &self->records[self->current]);
}

#ifdef NON_MATCHING
#include "ps2/vu0_lowering.h"
/* UNVERIFIED: the actor's scaled vector at +0x1B0 is assembly-derived;
 * its units remain unknown. XYZ prediction retains the original point's W. */
static inline BkVuVector RecordPredictionScalar(f32 value) {
    s32 word;
    BkVuVector result;
    __asm__("mfc1 wordv, floatv\n\tqmtc2.ni wordv, resultv"
            : "=r wordv"(word), "=j resultv"(result) : "f floatv"(value));
    return result;
}
/* The returned quadword crosses the native integer/VU register-bank boundary. */
static inline s128 RecordPredictionWords(BkVuVector value) {
    s128 result;
    __asm__("qmfc2.ni resultv, valuev" : "=r resultv"(result) : "j valuev"(value));
    return result;
}
static inline BkVuVector RecordPredictionAddTo(BkVuVector point, BkVuVector displacement) {
    __asm__("vadd.xyz pointv, pointv, displacementv" : "+j pointv"(point) : "j displacementv"(displacement));
    return point;
}
// Unmatched: scalar and point VU lifetimes differ at the multiply boundary.
s128 func_001890D0(Recovered_ActorRecords* self, f32 scale) {
    s128 result;
    if (!func_00188F10(self)) {
        result = M2C_FIELD(M2C_FIELD(self->owner, void**, 0x7C), s128*, 0xA0);
    } else {
        if (!ActorSlot_IsState0(func_00188F80(self))) {
            result = func_00189048(self);
        } else {
            Recovered_ManagedActor* actor = func_00188F80(self)->actor;
            s128 position = func_00189048(self);
            BkVuVector scalar = RecordPredictionScalar(scale);
            BkVuVector displacement = BkVuScaleXYZ(M2C_FIELD(actor, s128*, 0x1B0), scalar);
            result = RecordPredictionWords(RecordPredictionAddTo(position, displacement));
        }
    }
    return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_188bf8", func_001890D0);
#endif

s128 func_00189178(Recovered_ActorRecords* self, Recovered_ActorRecord* record) {
    return func_00178E60(ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), record->id));
}
