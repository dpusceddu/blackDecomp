#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/actor_records.h"
#include "game/actor/vector_math.h"
#include "ps2/vu0_math.h"

extern s32 func_00188F10(Recovered_ActorRecords*);
extern void* func_00188F80(Recovered_ActorRecords*);
extern s32 func_00189740(s32, void*, M2C_UNK);
extern void* D_0040F4D0;
extern s32 func_001792B0(s32);
extern s32 D_0040F4D4;
extern void* func_00174040(void*);
extern void* func_001740A0(void*, void*);
extern s32 func_0018DDD8(void*);
extern void* func_0013D400(void*);
extern void* func_00179258(s32, s32);
extern f32 func_0018DAE8(void*);
extern s128 func_00189048(Recovered_ActorRecords*);
extern s128* func_001893A0(Recovered_ActorRecords*);
extern s32 func_00178F18(void*);
extern s32 func_001897E8(Recovered_ActorRecords*, s32, s32);
extern void func_00188A40(void*, s32);
void func_0018A790(Recovered_ActorRecords*, void*);
void ActorRecords_CopyPeerRecord(Recovered_ActorRecords*, s32, void*);

void ActorRecords_ImportEligiblePeer(Recovered_ActorRecords* self) {
    if (!func_00188F10(self)) {
        void* other = func_00174040((s8*)self->owner + 0x1EF8);
        while (other != NULL) {
            if (M2C_FIELD(other, u8*, 0x78) && M2C_FIELD(other, void**, 0x7C) != NULL &&
                M2C_FIELD(M2C_FIELD(other, void**, 0x7C), s32*, 0x3A4) ==
                    M2C_FIELD(M2C_FIELD(self->owner, void**, 0x7C), s32*, 0x3A4) &&
                func_00188F10((Recovered_ActorRecords*)((s8*)other + 0x150))) {
                func_0018A790(self, other);
                return;
            }
            other = func_001740A0((s8*)self->owner + 0x1EF8, other);
        }
    }
}

void* ActorRecords_CurrentOrFallback(Recovered_ActorRecords* self) {
    void* result;
    if (func_00188F10(self)) {
        result = func_00188F80(self);
    } else {
        s32 id;
        if (func_0018DDD8((s8*)self->owner + 0xC94)) {
            id = M2C_FIELD(func_0013D400(self->owner), s32*, 0x30);
        } else {
            id = M2C_FIELD(D_0040F4D0, s32*, 0x3B0);
        }
        result = func_00179258(D_0040F4D4 + 0xFA8, id);
    }
    return result;
}

#ifdef NON_MATCHING
// Unmatched: VU constant lifetime and byte-predicate materialization differ.
s128 func_0018A6F0(Recovered_ActorRecords* self) {
    f32 radius = func_0018DAE8((s8*)self->owner + 0xC94);
    s128 position = func_00189048(self);
    BkVectorPS2 stored = *func_001893A0(self);
    BkVectorPS2 delta = BkVuSubXYZ(position, stored);
    f32 distanceSquared = BkSumPS2(BkMultiplyPS2(delta, delta));
    u8 within = distanceSquared < radius * radius;
    if (within) return position;
    return stored;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A6F0);
#endif

#ifdef NON_MATCHING
// Unmatched: invalid-record constant and iterator setup order differ.
void func_0018A790(Recovered_ActorRecords* self, void* other) {
    {
        Recovered_ActorRecord* record = (Recovered_ActorRecord*)((s8*)other + 0x150);
        s32 i;
        for (i = 0; i < 3; i++, record++) {
            if (record->id != -1) ActorRecords_CopyPeerRecord(self, record->id, other);
        }
    }
    if (self->current == -1) {
        f32 bestPriority = -1.0f;
        s32 best = -1;
        Recovered_ActorRecord* record;
        s32 i;
        s32 invalidId = -1;
        for (i = 0, record = self->records; i < 3; i++, record++) {
            if (bestPriority < record->priority && record->id != invalidId) {
                bestPriority = record->priority;
                best = i;
            }
        }
        if (best != -1) {
            void* destination = (s8*)self->owner + 0x290;
            void* current;
            self->current = best;
            current = func_00188F80(self);
            func_00188A40(destination, M2C_FIELD(current, s32*, 0));
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A790);
#endif

void func_0018A890(s32 arg0) {
    if (!func_00188F10((Recovered_ActorRecords*)arg0)) { func_00189740(arg0, D_0040F4D0 + 0x30, 1); }
}

void ActorRecords_CopyPeerRecord(Recovered_ActorRecords* self, s32 id, void* other) {
    void* object = func_00179258(D_0040F4D4 + 0xFA8, id);
    if (func_00178F18(object)) {
        s32 index = func_001897E8(self, id, 0);
        if (index != -1) {
            Recovered_ActorRecord* destination = (Recovered_ActorRecord*)((index * 0x60) + (u32)self);
            Recovered_ActorRecord* source = (Recovered_ActorRecord*)((s8*)other + 0x150);
            s32 i = 0;
            do {
                if (source->id == id) {
                    f32 timestamp;
                    destination->unk_05 = source->unk_05;
                    destination->position = source->position;
                    destination->unk_40 = source->unk_40;
                    destination->unk_50 = source->unk_50;
                    destination->unk_30 = source->unk_30;
                    timestamp = source->startTime;
                    destination->unk_1C = -1.0f;
                    destination->startTime = timestamp;
                    destination->unk_07 = source->unk_07;
                    destination->priority = source->priority;
                    return;
                }
                i++;
                source++;
            } while (i < 3);
        }
    }
}

void func_0018A9C8(s32 arg0, s32 arg1, s32 arg2) {
    ActorRecords_CopyPeerRecord((Recovered_ActorRecords*)arg0, func_001792B0(D_0040F4D4 + 0xFA8), (void*)arg2);
}
