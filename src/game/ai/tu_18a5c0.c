#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/actor_records.h"
#include "game/actor_slots.h"
#include "ps2/vu0_lowering.h"

extern s32 func_00188F10(Recovered_ActorRecords*);
extern Recovered_ActorSlot* func_00188F80(Recovered_ActorRecords*);
extern s32 func_00189740(Recovered_ActorRecords*, Recovered_ManagedActor*, s32);
extern void* D_0040F4D0;
extern Recovered_AIManager* D_0040F4D4;
extern void* func_00174040(void*);
extern void* func_001740A0(void*, void*);
extern s32 func_0018DDD8(void*);
extern void* func_0013D400(void*);
extern f32 func_0018DAE8(void*);
extern s128 func_00189048(Recovered_ActorRecords*);
extern s128* func_001893A0(Recovered_ActorRecords*);
extern s32 func_001897E8(Recovered_ActorRecords*, s32, s32);
extern void func_00188A40(void*, s32);
void func_0018A790(Recovered_ActorRecords*, Recovered_ManagedSlot*);
void ActorRecords_CopyPeerRecord(Recovered_ActorRecords*, s32, void*);

void ActorRecords_ImportEligiblePeer(Recovered_ActorRecords* self) {
    if (!func_00188F10(self)) {
        Recovered_ManagedSlot* other = func_00174040((u8*)self->owner + 0x1EF8);
        while (other != NULL) {
            if (other->active && other->actor != NULL &&
                other->actor->groupKey == ((Recovered_ManagedSlot*)self->owner)->actor->groupKey &&
                func_00188F10(&other->records)) {
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
        result = ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), id);
    }
    return result;
}

#ifdef NON_MATCHING
// Unmatched: native byte-boolean result retains a mask that the compiler removes.
s128 func_0018A6F0(Recovered_ActorRecords* self) {
    f32 radius = func_0018DAE8((u8*)self->owner + 0xC94);
    s128 position = func_00189048(self);
    BkVuVector stored = *func_001893A0(self);
    BkVuVector one = BkVuOneX();
    BkVuVector delta = BkVuSubXYZ(position, stored);
    f32 squared = __ee_vu_read_x(BkVuSumXYZ(BkVuMulXYZ(delta, delta), one));
    u8 within = squared < radius * radius;
    if (within) return position;
    return stored;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A6F0);
#endif

#ifdef NON_MATCHING
// Unmatched: countdown and receiver register allocation and invalid-id setup order differ.
void func_0018A790(Recovered_ActorRecords* self, Recovered_ManagedSlot* peer) {
    {
        s32 remaining = 2;
        Recovered_ActorRecord* record = peer->records.records;
        do {
            if (record->id != -1) ActorRecords_CopyPeerRecord(self, record->id, peer);
            --remaining;
            ++record;
        } while (remaining >= 0);
    }
    if (self->current == -1) {
        Recovered_ActorRecord* record;
        f32 bestPriority = -1.0f;
        s32 best = -1;
        s32 i;
        s32 invalidId = -1;
        for (i = 0, record = self->records; i < 3; ++i, ++record) {
            if (bestPriority < record->priority && record->id != invalidId) {
                bestPriority = record->priority;
                best = i;
            }
        }
        if (best != -1) {
            void* destination = (u8*)self->owner + 0x290;
            Recovered_ActorSlot* current;
            self->current = best;
            current = func_00188F80(self);
            func_00188A40(destination, current->index);
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_18a5c0", func_0018A790);
#endif

void func_0018A890(Recovered_ActorRecords* self) {
    if (!func_00188F10(self)) {
        func_00189740(self, (Recovered_ManagedActor*)((u8*)D_0040F4D0 + 0x30), 1);
    }
}

void ActorRecords_CopyPeerRecord(Recovered_ActorRecords* self, s32 id, void* other) {
    Recovered_ActorSlot* object =
        ActorSlotTable_GetEntry((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), id);
    if (ActorSlot_IsState0(object)) {
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

void func_0018A9C8(Recovered_ActorRecords* self, Recovered_ManagedActor* actor, Recovered_ManagedSlot* peer) {
    ActorRecords_CopyPeerRecord(
        self, ActorSlotTable_FindState0Actor((Recovered_ActorSlotTable*)((u8*)D_0040F4D4 + 0xFA8), actor), peer);
}
