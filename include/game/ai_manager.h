#ifndef GAME_AI_MANAGER_H
#define GAME_AI_MANAGER_H
#include "game/actor_records.h"
#include "game/effects/random_state.h"

/* Partial native views; original class identities and full actor allocations
 * are unknown. groupKey is the word compared when filtering peer records. */
typedef struct {
    u8 unk_00[0x20];
    s128 unk_20; // Native actor +0x90 axis; its broader role remains unknown.
    s128 position;
} Recovered_ManagedTransform;

typedef struct Recovered_ManagedSlot Recovered_ManagedSlot;
struct Recovered_ManagedSlotDispatch;

typedef struct {
    u8 unk_00[0x70];
    Recovered_ManagedTransform transform;
    u8 unk_B0[4];
    void* body; // Confirmed at +0xb4 by the exact RenderableState::Update body access.
    u8 unk_B8[0xC];
    s32 unk_C4; // Native actor category; the gameplay meaning of category 2 is unknown.
    u8 unk_C8[0x230];
    f32 unk_2F8; // UNVERIFIED: native creation writes FLT_MAX or 100.0; original field role is unknown.
    u8 unk_2FC[0x14];
    f32 unk_310;
    f32 unk_314;
    u8 unk_318[0x14];
    Recovered_ManagedSlot* managedSlot;
    u8 unk_330[0x50];
    s32 recordId; // Actor-slot id used by record lookup.
    u8 unk_384[8];
    u32 invalid; // Native state word: the vector callback skips 2; nonzero registration guard remains a draft.
    u8 unk_390[0x10];
    s32 unk_3A0;
    u32 groupKey;
    u8 unk_3A8[5];
    u8 controlsChanged;
    u8 unk_3AE[6];
    u8 unk_3B4;
    u8 unk_3B5;
    u8 unk_3B6;
    u8 unk_3B7;
} Recovered_ManagedActor;

struct Recovered_ManagedSlot {
    u8 unk_00[0x50];
    s128 unk_50; // UNVERIFIED: fallback vector consumer remains a draft.
    u8 unk_60[0x18];
    u8 active;
    u8 unk_79[3];
    Recovered_ManagedActor* actor;
    s32 unk_80; // UNVERIFIED: query eligibility compares this native word with 1.
    struct Recovered_ManagedSlotDispatch* dispatch84; // Adjusted vector-event dispatch; class identity remains unknown.
    u8 unk_88[0xC8];
    Recovered_ActorRecords records;
    u8 unk_290[0x460];
    u8 events[0x5A4];
    u8 query[0x125C];
    Recovered_ManagedSlot* freeNext;
    u8 unk_1EF4[0xDC];
};

typedef struct {
    u8 unk_00[0xA48];
    u8 unk_A48[0x28C];
    u8 unk_CD4[0x46C];
    void* sink;
    u8 unk_1144[0x19BC];
    Recovered_ManagedSlot slots[16];
    u8 unk_22800[0x3BC];
    Recovered_ManagedSlot* freeHead;
    BkEffectRandomStatePS2 random;
} Recovered_AIManager;

/* Only accessed spans are modeled; full actor/component extents remain unknown.
 * Existing exact 0x135e28/0x135ea8 accesses confirm mode and scalar-control fields;
 * 0x135c78 confirms the changed byte. Their broader gameplay roles remain open. */
typedef char ManagedActor2F8Offset[(u32)&((Recovered_ManagedActor*)0)->unk_2F8 == 0x2F8 ? 1 : -1];
typedef char ManagedActorBodyOffset[(u32)&((Recovered_ManagedActor*)0)->body == 0xB4 ? 1 : -1];
typedef char ManagedActorControlModeOffset[(u32)&((Recovered_ManagedActor*)0)->unk_3A0 == 0x3A0 ? 1 : -1];
typedef char ManagedActorControlChangedOffset[(u32)&((Recovered_ManagedActor*)0)->controlsChanged == 0x3AD ? 1 : -1];
typedef char ManagedSlotDispatchOffset[(u32)&((Recovered_ManagedSlot*)0)->dispatch84 == 0x84 ? 1 : -1];
typedef char ManagedActorSlotPointerOffset[(u32)&((Recovered_ManagedActor*)0)->managedSlot == 0x32C ? 1 : -1];
typedef char ManagedSlotStride[sizeof(Recovered_ManagedSlot) == 0x1FD0 ? 1 : -1];
typedef char ManagedSlotRecords[(u32) & ((Recovered_ManagedSlot*)0)->records == 0x150 ? 1 : -1];
typedef char ManagedSlotEvents[(u32) & ((Recovered_ManagedSlot*)0)->events == 0x6F0 ? 1 : -1];
typedef char ManagedSlotQuery[(u32) & ((Recovered_ManagedSlot*)0)->query == 0xC94 ? 1 : -1];
typedef char ManagerSlots[(u32) & ((Recovered_AIManager*)0)->slots == 0x2B00 ? 1 : -1];
typedef char ManagerRandom[(u32) & ((Recovered_AIManager*)0)->random == 0x22BC0 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

Recovered_ManagedSlot* Actor_GetManagedSlot(Recovered_ManagedActor* actor);

void* AIManager_TryGetSelection(void* self, s32 index);
s32 AIManager_HasFreeSlot(Recovered_AIManager* self);
Recovered_ManagedSlot* AIManager_PopFreeSlot(Recovered_AIManager* self);
void AIManager_PushFreeSlot(Recovered_AIManager* self, Recovered_ManagedSlot* slot);
f32 AIManager_RandomUnit(Recovered_AIManager* self);
f32 AIManager_RandomRange(Recovered_AIManager* self, f32 minimum, f32 maximum);
s32 AIManager_RandomInteger(Recovered_AIManager* self, s32 minimum, s32 maximum);
s32 AIManager_TestProbability(Recovered_AIManager* self, f32 probability);
void AIManager_BroadcastVectorPair(Recovered_AIManager* self, s128 first, s128 second, s32 kind);
void AIManager_BroadcastActor(Recovered_AIManager* self, Recovered_ManagedActor* actor);
void AIManager_ForwardVector(Recovered_AIManager* self, s128 value);
void AIManager_ForwardVectorWithKind(Recovered_AIManager* self, s128 value, s32 kind);
void AIManager_SetSelection(Recovered_AIManager* self, s32 selection);
Recovered_ManagedSlot* AIManager_FindNearestEligibleSlot(Recovered_AIManager* self, s128 position);
#ifdef __cplusplus
}
#endif
#endif
