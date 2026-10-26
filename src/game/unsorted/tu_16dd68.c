#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/ai_manager.h"
#include "game/actor/vector_math.h"
#include "ps2/vu0_math.h"

extern s32 func_00179640(void*);
extern void* func_00179668(void*, s32);
extern void func_001842C8(void*, s128, Recovered_ManagedActor*, f32);
extern void func_001843C0(void*, s128, s128, s32);
extern void func_00184550(void*, Recovered_ManagedActor*, f32);
extern void func_0013D8D8(Recovered_ManagedSlot*, s128);
extern void func_0013D9A0(Recovered_ManagedSlot*, s128, s32);
extern void func_001895C8(Recovered_ActorRecords*, Recovered_ManagedSlot*, Recovered_ManagedActor*);
extern void func_001794B0(void*, s8);
extern void func_00175DB8(void*, s32);
extern void func_0017BCD8(void*, s32);
extern void func_00289698(void*, void*);
extern s32 func_0018DDD8(void*);
extern Recovered_AIManager* D_0040F4D4;
extern const f32 D_003F534C;

static inline f32 ManagerRandomFraction(Recovered_AIManager* self) {
    return (f32)BkEffectRandomSignedStepPS2(&self->random) * 2.3283064365386963e-10f;
}

void* AIManager_TryGetSelection(void* self, s32 index) {
    void* result;
    if (!func_00179640(self))
        result = NULL;
    else
        result = func_00179668(self, index);
    return result;
}

s32 AIManager_HasFreeSlot(Recovered_AIManager* self) { return self->freeHead != NULL; }

Recovered_ManagedSlot* AIManager_PopFreeSlot(Recovered_AIManager* self) {
    Recovered_ManagedSlot* slot = self->freeHead;
    self->freeHead = slot->freeNext;
    return slot;
}

void AIManager_PushFreeSlot(Recovered_AIManager* self, Recovered_ManagedSlot* slot) {
    slot->freeNext = self->freeHead;
    self->freeHead = slot;
}

f32 AIManager_RandomUnit(Recovered_AIManager* self) { return ManagerRandomFraction(self); }
f32 AIManager_RandomRange(Recovered_AIManager* self, f32 minimum, f32 maximum) {
    return minimum + (maximum - minimum) * ManagerRandomFraction(self);
}
s32 AIManager_RandomInteger(Recovered_AIManager* self, s32 minimum, s32 maximum) {
    f32 lower = (f32)minimum;
    f32 upper = (f32)maximum + 1.0f - 0.0000152587890625f;
    return (s32)(lower + (upper - lower) * ManagerRandomFraction(self));
}
s32 AIManager_TestProbability(Recovered_AIManager* self, f32 probability) {
    if (probability == 0.0f) return 0;
    return AIManager_RandomUnit(self) <= probability;
}

#include "ps2/recovered_types.h"
extern s8 * func_00172C88(void *, s128, s128);
extern Recovered_ManagedSlot* AIManager_FindNearestEligibleSlot(Recovered_AIManager*, s128);
extern s8 * func_00181F48(void *, s32, s32, f32, f32);

s8 * func_0016E2B8(void *arg0, s128 arg1, s128 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s8 *var_2;

    if (arg3 != 0) {
        return func_00172C88(arg0 + 0x22800, arg1, arg2);
    }
    var_2 = (s8*)AIManager_FindNearestEligibleSlot(arg0, arg2);
    if (var_2 != NULL) {
        var_2 = func_00181F48(var_2 + 0xC80, 0, 0x11, 0.0f, 1.0f);
    }
    return var_2;
}

#ifdef NON_MATCHING
// Unmatched: conditional branches and peer-record iterator scheduling differ.
void func_0016E318(Recovered_AIManager* self, Recovered_ManagedActor* ignored, Recovered_ManagedSlot* peer) {
    Recovered_ManagedSlot* slot = self->slots;
    u8* records = (u8*)&slot->records;
    s32 i;
    for (i = 15; i >= 0; records += sizeof(*slot), i--, slot++) {
        if (slot->active && slot->actor != NULL && slot->actor->groupKey == peer->actor->groupKey &&
            slot->actor != ignored && slot != peer) {
            func_001895C8((Recovered_ActorRecords*)records, peer, ignored);
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E318);
#endif
void AIManager_SetSelection(Recovered_AIManager* self, s32 selection) {
    Recovered_AIManager* manager;
    void* selected;
    func_001794B0(self, (s8)selection);
    func_00175DB8(self->unk_A48, selection);
    func_0017BCD8(self->unk_CD4, selection);
    manager = D_0040F4D4;
    selected = AIManager_TryGetSelection(self, 1);
    func_00289698(manager->sink, selected);
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_16dd68", func_0016E430);
Recovered_ManagedSlot* AIManager_FindNearestEligibleSlot(Recovered_AIManager* self, s128 position) {
    Recovered_ManagedSlot* slot = self->slots;
    u8* query = slot->query;
    Recovered_ManagedSlot* nearest = NULL;
    f32 nearestDistance = D_003F534C;
    s32 i;
    for (i = 15; i >= 0; slot++, i--, query += sizeof(*slot)) {
        if (slot->active && !func_0018DDD8(query)) {
            BkVectorPS2 delta = BkVuSubXYZ(slot->actor->transform.position, position);
            f32 distanceSquared = BkSumPS2(BkMultiplyPS2(delta, delta));
            if (distanceSquared < nearestDistance) {
                nearestDistance = distanceSquared;
                nearest = slot;
            }
        }
    }
    return nearest;
}

const f32 D_003F534C = 3.40282346638528859812e38F;
