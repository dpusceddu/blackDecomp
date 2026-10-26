#include "include_asm.h"
#include "game/ai/actor_slot_values.h"
#include "game/ai/actor_creation.h"

extern Recovered_AIManager* D_0040F4D4;
extern const s128 D_004432A0;
extern const s128 D_004432B0;
extern const s128* func_00162570(Recovered_ActorBinding*);
/* Native actor +0x210 receiver; the component's class identity is unknown. */
extern s128 func_00173488(void*);

extern void* D_0040F4D0;
extern Recovered_ManagedSlot* func_00178AE8(Recovered_ActorCreationScope*, s32, s32,
    Recovered_ActorCreationRequest*, Recovered_ActorCreationDescriptor*, void*, u64, u64);
extern Recovered_ManagedSlot* func_00178978(Recovered_ActorCreationScope*, s32,
    Recovered_ActorCreationRequest*, Recovered_ActorCreationDescriptor*, void*, u64, u64, u32, u32, u32, u32);
Recovered_ManagedActor* func_001784F0(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64);
Recovered_ManagedActor* func_001785F0(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64);
Recovered_ManagedActor* func_00178650(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64);
Recovered_ManagedActor* func_001786B0(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64, u32, u32, u32, u32);
Recovered_ManagedActor* func_00178718(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64, u32, u32, u32, u32);
Recovered_ManagedActor* func_00178780(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64, u32, u32, u32, u32);
Recovered_ManagedActor* func_001787E8(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64, u32, u32, u32, u32);
Recovered_ManagedActor* func_00178840(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64, u32, u32, u32, u32);
Recovered_ManagedActor* func_001788A8(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64, u32, u32, u32, u32);
Recovered_ManagedActor* func_00178910(Recovered_ActorCreationScope*,
    Recovered_ActorCreationRequest*, void*, u64, u32, u32, u32, u32);


/* Actor-slot forwarding and value access. This file follows the existing
 * proposed split; the original source/TU identity remains unknown. */
Recovered_ManagedActor* func_00178408(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    switch (request->kind) {
        case 0: return func_001784F0(self, request, context, key);
        case 1: return func_00178650(self, request, context, key);
        case 2: return func_001785F0(self, request, context, key);
        case 3: return func_001786B0(self, request, context, key, arg4, arg5, arg6, arg7);
        case 4: return func_00178718(self, request, context, key, arg4, arg5, arg6, arg7);
        case 5: return func_00178780(self, request, context, key, arg4, arg5, arg6, arg7);
        case 6: return func_001787E8(self, request, context, key, arg4, arg5, arg6, arg7);
        case 7: return func_00178840(self, request, context, key, arg4, arg5, arg6, arg7);
        case 8: return func_001788A8(self, request, context, key, arg4, arg5, arg6, arg7);
        case 9: return func_00178910(self, request, context, key, arg4, arg5, arg6, arg7);
        default: return NULL;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_001784F0);
Recovered_ManagedActor* func_001785F0(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot;
    if (!key) key = descriptor->key;
    slot = func_00178AE8(self, 0x1d, 1, request, descriptor, context, key, 0x5446127ad7970000UL);
    if (!slot) return NULL;
    return slot->actor;
}

Recovered_ManagedActor* func_00178650(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot;
    if (!key) key = descriptor->key;
    slot = func_00178AE8(self, 0x1e, 1, request, descriptor, context, key, 0x5446127ad7970000UL);
    if (!slot) return NULL;
    return slot->actor;
}

/* Forward the native trailing words unchanged. Only their downstream uses, including one low-byte use,
 * are known; their original parameter meanings remain unresolved. */
Recovered_ManagedActor* func_001786B0(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot = func_00178978(self, 0x24, request, descriptor, context, key,
        ActorCreation_Resources(D_0040F4D0)->unk_2C8, arg4, arg5, arg6, arg7);
    if (!slot) return NULL;
    return slot->actor;
}

Recovered_ManagedActor* func_00178718(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot = func_00178978(self, 0x25, request, descriptor, context, key,
        ActorCreation_Resources(D_0040F4D0)->unk_2D0, arg4, arg5, arg6, arg7);
    if (!slot) return NULL;
    return slot->actor;
}

Recovered_ManagedActor* func_00178780(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot = func_00178978(self, 0x26, request, descriptor, context, key,
        ActorCreation_Resources(D_0040F4D0)->unk_2D8, arg4, arg5, arg6, arg7);
    if (!slot) return NULL;
    return slot->actor;
}

Recovered_ManagedActor* func_001787E8(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot = func_00178978(self, 0x27, request, descriptor, context, key,
        descriptor->unk_28, arg4, arg5, arg6, arg7);
    if (!slot) return NULL;
    return slot->actor;
}

Recovered_ManagedActor* func_00178840(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot = func_00178978(self, 0x28, request, descriptor, context, key,
        ActorCreation_Resources(D_0040F4D0)->unk_2E0, arg4, arg5, arg6, arg7);
    if (!slot) return NULL;
    return slot->actor;
}

Recovered_ManagedActor* func_001788A8(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot = func_00178978(self, 0x29, request, descriptor, context, key,
        ActorCreation_Resources(D_0040F4D0)->unk_2E8, arg4, arg5, arg6, arg7);
    if (!slot) return NULL;
    return slot->actor;
}

Recovered_ManagedActor* func_00178910(Recovered_ActorCreationScope* self, Recovered_ActorCreationRequest* request,
    void* context, u64 key, u32 arg4, u32 arg5, u32 arg6, u32 arg7) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot = func_00178978(self, 0x2a, request, descriptor, context, key,
        ActorCreation_Resources(D_0040F4D0)->unk_2F0, arg4, arg5, arg6, arg7);
    if (!slot) return NULL;
    return slot->actor;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178978);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178AE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178BC0);
/* Return the position storage selected by the native slot tag. */
const s128* func_00178D30(Recovered_ActorSlot* entry) {
    switch (entry->state) {
    case 0:
        return &entry->actor->transform.position;
    case 1:
        return func_00162570((Recovered_ActorBinding*)entry->actor);
    case 2: {
        Recovered_ActorSlotIndirect* indirect = (Recovered_ActorSlotIndirect*)entry->actor;
        Recovered_ActorSlotPositionGroup** groups = ActorSlot_PositionGroups(D_0040F4D4);
        groups += indirect->actor->groupKey;
        return (*groups)->position;
    }
    case 3:
        return (const s128*)entry->actor;
    default:
        return &D_004432A0;
    }
}

/* Binding and direct-point slots use the default second vector. Its role is unknown. */
const s128* func_00178DE0(Recovered_ActorSlot* entry) {
    switch (entry->state) {
    case 0:
        return ActorSlot_ActorVector(entry->actor);
    case 1:
        return &D_004432B0;
    case 2: {
        Recovered_ActorSlotIndirect* indirect = (Recovered_ActorSlotIndirect*)entry->actor;
        return ActorSlot_ActorVector(indirect->actor);
    }
    case 3:
        return &D_004432B0;
    default:
        return &D_004432B0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178E50);
/* Actors sample their history; bindings sample their descriptor, while other tags copy a stored point. */
s128 func_00178E60(Recovered_ActorSlot* entry) {
    switch (entry->state) {
    case 0:
        return func_00173488((u8*)entry->actor + 0x210);
    case 1:
        return ActorBinding_SamplePosition((Recovered_ActorBinding*)entry->actor);
    case 2: {
        Recovered_ActorSlotIndirect* indirect = (Recovered_ActorSlotIndirect*)entry->actor;
        Recovered_ActorSlotPositionGroup** groups = ActorSlot_PositionGroups(D_0040F4D4);
        groups += indirect->actor->groupKey;
        return *(*groups)->position;
    }
    case 3:
        return *(const s128*)entry->actor;
    default:
        return D_004432A0;
    }
}

