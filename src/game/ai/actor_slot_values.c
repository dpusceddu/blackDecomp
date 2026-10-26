#include "include_asm.h"
#include "game/ai/actor_slot_values.h"
#include "game/ai/actor_creation.h"
#ifdef NON_MATCHING
#include "game/weapons/inventory.h"
#endif

extern Recovered_AIManager* D_0040F4D4;
extern const s128 D_004432A0;
extern const s128 D_004432B0;
extern const s128* func_00162570(Recovered_ActorBinding*);
/* Native actor +0x210 receiver; the component's class identity is unknown. */
extern s128 func_00173488(void*);

extern void* D_0040F4D0;

#ifdef NON_MATCHING
extern BkWeaponCatalogOwnerPS2* D_0040F4E0;
extern BkWeaponControllerPS2* func_0015CEF0(BkWeaponCatalogOwnerPS2*, Recovered_ManagedActor*, s8, u32);
extern void func_00137B08(Recovered_ManagedActor*, u8);
extern void func_0016ABA8(void*, s32, s32, void*);
extern void func_001551A0(BkInventoryPS2*, s32);
extern void* func_00138C40(void*, s32);
extern s8 func_0012BDC8(void*, s32);
extern Recovered_ManagedActor* func_00138C80(void*, Recovered_ManagedSlot*, Recovered_ActorCreationPacket*);
#endif

extern void* D_0040F514;
extern s32 func_001390F8(void*);
extern Recovered_ManagedSlot* func_00178BC0(Recovered_ActorCreationScope*, s32, s32, u64,
    Recovered_ActorCreationRequest*, Recovered_ActorCreationDescriptor*, u64, s32, u32, u32, s32, u32);

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

#ifdef NON_MATCHING
static inline s8 ActorCreation_FindWeaponKey(BkWeaponCatalogOwnerPS2* manager, u64 key) {
    BkWeaponCatalogPS2* catalog = manager->catalog;
    s8 index = 0;
    s32 count = catalog->count;
    if (count) {
        BkWeaponCatalogRowPS2* row = catalog->rows;
        do {
            if (row->identity == key) return index;
            row++;
            index++;
        } while (index < count);
    }
    return -1;
}
/* Kind 0x1f installs the requested catalog weapon in actor weapon slot 1.
 * The hardcoded resource-key meanings remain unknown. */
// Unmatched: catalog search register allocation differs.
Recovered_ManagedActor* func_001784F0(Recovered_ActorCreationScope* self,
    Recovered_ActorCreationRequest* request, void* context, u64 key) {
    Recovered_ActorCreationDescriptor* descriptor = request->descriptor;
    Recovered_ManagedSlot* slot;
    BkWeaponControllerPS2* weapon;
    if (!key) key = descriptor->key;
    slot = func_00178AE8(self, 0x1F, 1, request, descriptor, context, key, 0x5446127AD7970000UL);
    if (!slot) return NULL;
    weapon = func_0015CEF0(D_0040F4E0, slot->actor,
        ActorCreation_FindWeaponKey(D_0040F4E0, 0x54461524b8230000UL), 0);
    ActorCreation_WeaponSlots(slot->actor)[1] = weapon;
    return slot->actor;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_001784F0);
#endif
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

#ifdef NON_MATCHING
// Unmatched: descriptor and slot register allocation differs.
Recovered_ManagedSlot* func_00178978(Recovered_ActorCreationScope* self, s32 kind,
    Recovered_ActorCreationRequest* request, Recovered_ActorCreationDescriptor* descriptor,
    void* context, u64 key, u64 resourceKey, u32 arg7, u32 arg8, u32 arg9, u32 arg10) {
    u8 descriptorMode = descriptor->unk_57;
    u8 flag = arg10;
    Recovered_ManagedSlot* slot;
    if (!func_001390F8(D_0040F514)) return NULL;
    if (!key) key = descriptor->key;
    slot = func_00178BC0(self, kind, descriptorMode, key, request, descriptor, resourceKey,
        1, arg7, arg8, arg9, flag);
    if (!slot) return NULL;
    func_00137B08(slot->actor, descriptor->unk_5A != 0);
    {
        u8 option = descriptor->unk_54;
        if (option) {
            u32 value = descriptor->unk_34;
            slot->unk_1FC8 = option;
            slot->unk_1FC4 = value;
        }
    }
    if (descriptor->unk_53) {
        func_0016ABA8((u8*)slot + 0x1F90, descriptor->unk_30, descriptor->unk_53, slot->actor);
    }
    if (descriptor->unk_5D) {
        Recovered_ManagedSlotQuery* query = ManagedSlot_Query(slot);
        f32 x = descriptor->unk_40;
        f32 y = descriptor->unk_44;
        f32 z = descriptor->unk_48;
        query->unk_1C = z;
        query->unk_14 = x;
        query->unk_18 = y;
        query->unk_20 = 1;
        func_001551A0((BkInventoryPS2*)((u8*)slot->actor + 0x280), descriptor->unk_5C);
    }
    return slot;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178978);
#endif
Recovered_ManagedSlot* func_00178AE8(Recovered_ActorCreationScope* self, s32 kind, s32 mode,
    Recovered_ActorCreationRequest* request, Recovered_ActorCreationDescriptor* descriptor,
    void* context, u64 key, u64 resourceKey) {
    if (func_001390F8(D_0040F514)) {
        Recovered_ManagedSlot* slot = func_00178BC0(self, kind, mode, key, request, descriptor,
            resourceKey, 0, 0, 0, -1, 0);
        if (slot) {
            slot->actor->unk_2F8 = 3.4028234663852886e+38f; /* Largest finite native float. */
            return slot;
        }
    }
    return NULL;
}

#ifdef NON_MATCHING
// Unmatched: retained descriptor store is scheduled early.
Recovered_ManagedSlot* func_00178BC0(Recovered_ActorCreationScope* self, s32 kind, s32 arg2, u64 key,
    Recovered_ActorCreationRequest* request, Recovered_ActorCreationDescriptor* descriptor, u64 resourceKey,
    s32 mode, u32 arg8, u32 arg9, s32 arg10, u32 arg11) {
    u8 flag = arg11;
    Recovered_ActorCreationPacket packet;
    Recovered_ManagedSlot* slot;
    Recovered_ManagedActor* actor;
    if (!AIManager_HasFreeSlot(D_0040F4D4)) return NULL;
    slot = AIManager_PopFreeSlot(D_0040F4D4);
    packet.definition = func_00138C40(D_0040F514, kind);
    packet.position = descriptor->position;
    packet.requestKey = request->key;
    packet.resourceKey = resourceKey;
    packet.unk_30 = arg10;
    packet.unk_34 = func_0012BDC8(D_0040F4D0, arg10);
    packet.scopeValue = self->count;
    packet.mode = mode;
    packet.kind = kind;
    packet.unk_44 = arg2;
    packet.key = key;
    packet.unk_58 = flag;
    if (mode == 1) packet.request = request;
    else packet.request = NULL;
    actor = func_00138C80(D_0040F514, slot, &packet);
    self->count++;
    actor->unk_2F8 = 100.0f;
    actor->unk_0C = arg9;
    actor->unk_08 = arg8;
    actor->unk_324 = descriptor;
    return slot;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178BC0);
#endif
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

