#ifndef GAME_AI_ACTOR_CREATION_H
#define GAME_AI_ACTOR_CREATION_H
#include "game/ai_manager.h"
#include "game/weapons/catalog.h"

/* Exact forwarding methods confirm request tags/descriptors, descriptor keys
 * and accessed resource keys. UNVERIFIED: unaccessed spans, original classes
 * and full object extents; remaining draft-only fields are marked below. */
typedef struct {
    u8 unk_00[0x20];
    u64 key;
    u64 unk_28;
} Recovered_ActorCreationDescriptor;

typedef struct {
    s32 kind;
    Recovered_ActorCreationDescriptor* descriptor;
    u64 key; // UNVERIFIED: the core creation consumer remains a draft.
} Recovered_ActorCreationRequest;

typedef struct {
    u32 count; // UNVERIFIED: the core creation increments this word; its original role is unknown.
} Recovered_ActorCreationScope;

typedef struct {
    u8 unk_00[0x2C8];
    u64 unk_2C8;
    u64 unk_2D0;
    u64 unk_2D8;
    u64 unk_2E0;
    u64 unk_2E8;
    u64 unk_2F0;
} Recovered_ActorCreationResources;

static inline Recovered_ActorCreationResources* ActorCreation_Resources(void* context) {
    return *(Recovered_ActorCreationResources**)((u8*)context + 0x5AEC);
}
/* UNVERIFIED: native kind1F creation stores a controller in slot1; its source
 * remains a draft. The number of slots and complete inventory extent are unknown. */
static inline BkWeaponControllerPS2** ActorCreation_WeaponSlots(Recovered_ManagedActor* actor) {
    return *(BkWeaponControllerPS2***)((u8*)actor + 0x2A0);
}

typedef char ActorCreationDescriptorKeyOffset[
    (u32)&((Recovered_ActorCreationDescriptor*)0)->key == 0x20 ? 1 : -1];
typedef char ActorCreationRequestDescriptorOffset[
    (u32)&((Recovered_ActorCreationRequest*)0)->descriptor == 4 ? 1 : -1];
typedef char ActorCreationResourceKeyOffset[
    (u32)&((Recovered_ActorCreationResources*)0)->unk_2F0 == 0x2F0 ? 1 : -1];
#endif
