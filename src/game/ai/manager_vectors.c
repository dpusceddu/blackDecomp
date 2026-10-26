#include "include_asm.h"
#include "game/ai_manager.h"

extern void func_0013D8D8(Recovered_ManagedSlot*, s128);
extern void func_0013D9A0(Recovered_ManagedSlot*, s128, s32);

#include "game/actor/vector_math.h"
#include "ps2/vu0_math.h"
extern void func_001842C8(void*, s128, Recovered_ManagedActor*, f32);
extern void func_001843C0(void*, s128, s128, s32);
extern void func_00184550(void*, Recovered_ManagedActor*, f32);

#ifdef NON_MATCHING
// Unmatched: position VU transfer and iterator setup precede the native kind guard.
void func_0016E008(Recovered_AIManager* self, s128 position, Recovered_ManagedActor* source, s32 kind) {
    if (kind != 11) {
        Recovered_ManagedSlot* slot = self->slots;
        u8* events = slot->events;
        s32 i;
        for (i = 15; i >= 0; events += sizeof(*slot), i--, slot++) {
            if (slot->active) {
                BkVectorPS2 delta = BkVuSubXYZ(slot->actor->transform.position, position);
                f32 distanceSquared = BkSumPS2(BkMultiplyPS2(delta, delta));
                func_001842C8(events, position, source, distanceSquared);
            }
        }
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/manager_vectors", func_0016E008);
#endif

void AIManager_BroadcastVectorPair(Recovered_AIManager* self, s128 first, s128 second, s32 kind) {
    Recovered_ManagedSlot* slot = self->slots;
    void* events = self->slots[0].events;
    s32 i;
    for (i = 15; i >= 0; events = (u8*)events + sizeof(*slot), i--, slot++) {
        if (slot->active) func_001843C0(events, first, second, kind);
    }
}

void AIManager_BroadcastActor(Recovered_AIManager* self, Recovered_ManagedActor* actor) {
    Recovered_ManagedSlot* slot = self->slots;
    u8* events = slot->events;
    Recovered_ManagedTransform* transform = &actor->transform;
    s32 i;
    for (i = 15; i >= 0; events += sizeof(*slot), i--, slot++) {
        if (slot->active && slot->actor != actor) {
            BkVectorPS2 delta = BkVuSubXYZ(slot->actor->transform.position, transform->position);
            f32 distanceSquared = BkSumPS2(BkMultiplyPS2(delta, delta));
            func_00184550(events, actor, distanceSquared);
        }
    }
}

void AIManager_ForwardVector(Recovered_AIManager* self, s128 value) {
    Recovered_ManagedSlot* slot = self->slots;
    s32 i;
    for (i = 15; i >= 0; i--, slot++) {
        if (slot->active) func_0013D8D8(slot, value);
    }
}

void AIManager_ForwardVectorWithKind(Recovered_AIManager* self, s128 value, s32 kind) {
    Recovered_ManagedSlot* slot = self->slots;
    s32 i;
    for (i = 15; i >= 0; i--, slot++) {
        if (slot->active) func_0013D9A0(slot, value, kind);
    }
}
