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
struct Recovered_ActorCreationDescriptor;
struct Recovered_ActorIndexedComponent;

typedef struct {
    u8 unk_00[8];
    u32 unk_08; // UNVERIFIED: assigned by the native core creation draft; original role is unknown.
    u8 unk_0C; // UNVERIFIED: assigned by the native core creation draft; original role is unknown.
    u8 unk_0D[0x63];
    Recovered_ManagedTransform transform;
    u8 unk_B0[4];
    void* body; // Confirmed at +0xb4 by the exact RenderableState::Update body access.
    void* unk_B8; // UNVERIFIED: native control routing forwards this pointer; original role is unknown.
    struct Recovered_ActorIndexedComponent* unk_BC; // Exact indexed scalar controls confirm this pointer; class identity is unknown.
    f32 unk_C0; // Exact 0x1378f0 scales this float; original units and gameplay role are unknown.
    s32 unk_C4; // Native actor category; the gameplay meaning of category 2 is unknown.
    u8 unk_C8[0x190];
    f32 unk_258; // Exact 0x137b08 writes a random integer minus a random float; gameplay role is unknown.
    u8 unk_25C[0x10];
    void* unk_26C; // Exact 0x137490 forwards this pointer; selector/table accesses remain UNVERIFIED drafts.
    u8 unk_270[0x34];
    void* unk_2A4; // UNVERIFIED: native slot-state predicate tests this pointer; original role is unknown.
    u8 unk_2A8[0x40];
    f32 unk_2E8; // UNVERIFIED: native geometry drafts use this vertical bound; original role is unknown.
    u8 unk_2EC[0xC];
    f32 unk_2F8; // UNVERIFIED: native creation writes FLT_MAX or 100.0; original field role is unknown.
    u8 unk_2FC[0x14];
    f32 unk_310;
    f32 unk_314;
    f32 unk_318; // UNVERIFIED: native horizontal-bound draft uses half this scalar; original role is unknown.
    u8 unk_31C[4];
    void* unk_320; // UNVERIFIED: native downward trace retains Hit +0x24 here; gameplay role is unknown.
    struct Recovered_ActorCreationDescriptor* unk_324; // UNVERIFIED: native creation retains its descriptor here.
    void* unk_328; // UNVERIFIED: native layer-kind predicate passes this record to the exact +4 getter.
    Recovered_ManagedSlot* managedSlot;
    u8 unk_330[0x50];
    s32 recordId; // Actor-slot id used by record lookup.
    u8 unk_384[8];
    u32 invalid; // Native state word: the vector callback skips 2; nonzero registration guard remains a draft.
    u8 unk_390[0x10];
    s32 unk_3A0;
    u32 groupKey;
    u8 unk_3A8[4];
    u8 unk_3AC; // Exact 0x137b08 confirms flag storage; its gameplay role is unknown.
    u8 controlsChanged;
    u8 unk_3AE[6];
    u8 unk_3B4;
    u8 unk_3B5;
    u8 unk_3B6;
    u8 unk_3B7;
} Recovered_ManagedActor;

/* UNVERIFIED: only the parameterized creation draft accesses these query
 * fields. Original class, gameplay roles and complete query extent are unknown. */
typedef struct {
    u8 unk_00[0x14];
    f32 unk_14, unk_18, unk_1C;
    u8 unk_20;
} Recovered_ManagedSlotQuery;

struct Recovered_ManagedSlot {
    u8 unk_00[0x31];
    u8 unk_31; // UNVERIFIED: native slot-state predicate tests this byte; original role is unknown.
    u8 unk_32[0x1E];
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
    u8 unk_1EF4[0xD0];
    u32 unk_1FC4; // UNVERIFIED: assigned by the parameterized creation draft; original role is unknown.
    u32 unk_1FC8; // UNVERIFIED: assigned from a descriptor byte by the same draft.
    u8 unk_1FCC[4];
};

static inline Recovered_ManagedSlotQuery* ManagedSlot_Query(Recovered_ManagedSlot* slot) {
    return (Recovered_ManagedSlotQuery*)slot->query;
}

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
typedef char ManagedActor08Offset[(u32)&((Recovered_ManagedActor*)0)->unk_08 == 8 ? 1 : -1];
typedef char ManagedActor0COffset[(u32)&((Recovered_ManagedActor*)0)->unk_0C == 0xC ? 1 : -1];
typedef char ManagedActor324Offset[(u32)&((Recovered_ManagedActor*)0)->unk_324 == 0x324 ? 1 : -1];
typedef char ManagedActorB8Offset[(u32)&((Recovered_ManagedActor*)0)->unk_B8 == 0xB8 ? 1 : -1];
typedef char ManagedActorBCOffset[(u32)&((Recovered_ManagedActor*)0)->unk_BC == 0xBC ? 1 : -1];
typedef char ManagedActorC0Offset[(u32)&((Recovered_ManagedActor*)0)->unk_C0 == 0xC0 ? 1 : -1];
typedef char ManagedActor258Offset[(u32)&((Recovered_ManagedActor*)0)->unk_258 == 0x258 ? 1 : -1];
typedef char ManagedActor3ACOffset[(u32)&((Recovered_ManagedActor*)0)->unk_3AC == 0x3AC ? 1 : -1];
typedef char ManagedActor26COffset[(u32)&((Recovered_ManagedActor*)0)->unk_26C == 0x26C ? 1 : -1];
typedef char ManagedActor2A4Offset[(u32)&((Recovered_ManagedActor*)0)->unk_2A4 == 0x2A4 ? 1 : -1];
typedef char ManagedActor328Offset[(u32)&((Recovered_ManagedActor*)0)->unk_328 == 0x328 ? 1 : -1];
typedef char ManagedSlot31Offset[(u32)&((Recovered_ManagedSlot*)0)->unk_31 == 0x31 ? 1 : -1];
typedef char ManagedActor2E8Offset[(u32)&((Recovered_ManagedActor*)0)->unk_2E8 == 0x2E8 ? 1 : -1];
typedef char ManagedActor318Offset[(u32)&((Recovered_ManagedActor*)0)->unk_318 == 0x318 ? 1 : -1];
typedef char ManagedActor320Offset[(u32)&((Recovered_ManagedActor*)0)->unk_320 == 0x320 ? 1 : -1];
typedef char ManagedActor2F8Offset[(u32)&((Recovered_ManagedActor*)0)->unk_2F8 == 0x2F8 ? 1 : -1];
typedef char ManagedActorBodyOffset[(u32)&((Recovered_ManagedActor*)0)->body == 0xB4 ? 1 : -1];
typedef char ManagedActorControlModeOffset[(u32)&((Recovered_ManagedActor*)0)->unk_3A0 == 0x3A0 ? 1 : -1];
typedef char ManagedActorControlChangedOffset[(u32)&((Recovered_ManagedActor*)0)->controlsChanged == 0x3AD ? 1 : -1];
typedef char ManagedSlotDispatchOffset[(u32)&((Recovered_ManagedSlot*)0)->dispatch84 == 0x84 ? 1 : -1];
typedef char ManagedActorSlotPointerOffset[(u32)&((Recovered_ManagedActor*)0)->managedSlot == 0x32C ? 1 : -1];
typedef char ManagedSlotStride[sizeof(Recovered_ManagedSlot) == 0x1FD0 ? 1 : -1];
typedef char ManagedSlotRecords[(u32) & ((Recovered_ManagedSlot*)0)->records == 0x150 ? 1 : -1];
typedef char ManagedSlotEvents[(u32) & ((Recovered_ManagedSlot*)0)->events == 0x6F0 ? 1 : -1];
typedef char ManagedSlotQuery14Offset[(u32)&((Recovered_ManagedSlotQuery*)0)->unk_14 == 0x14 ? 1 : -1];
typedef char ManagedSlotQuery20Offset[(u32)&((Recovered_ManagedSlotQuery*)0)->unk_20 == 0x20 ? 1 : -1];
typedef char ManagedSlot1FC4Offset[(u32)&((Recovered_ManagedSlot*)0)->unk_1FC4 == 0x1FC4 ? 1 : -1];
typedef char ManagedSlot1FC8Offset[(u32)&((Recovered_ManagedSlot*)0)->unk_1FC8 == 0x1FC8 ? 1 : -1];
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
