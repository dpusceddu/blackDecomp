#ifndef GAME_AI_MANAGER_H
#define GAME_AI_MANAGER_H
#include "game/actor_records.h"
#include "game/effects/random_state.h"

/* Partial native views; original class identities and full actor allocations
 * are unknown. groupKey is the word compared when filtering peer records. */
typedef struct {
    u8 unk_00[0x30];
    s128 position;
} Recovered_ManagedTransform;

typedef struct {
    u8 unk_00[0x70];
    Recovered_ManagedTransform transform;
    u8 unk_B0[0x2F4];
    u32 groupKey;
} Recovered_ManagedActor;

typedef struct Recovered_ManagedSlot Recovered_ManagedSlot;
struct Recovered_ManagedSlot {
    u8 unk_00[0x78];
    u8 active;
    u8 unk_79[3];
    Recovered_ManagedActor* actor;
    u8 unk_80[0xD0];
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

typedef char ManagedSlotStride[sizeof(Recovered_ManagedSlot) == 0x1FD0 ? 1 : -1];
typedef char ManagedSlotRecords[(u32) & ((Recovered_ManagedSlot*)0)->records == 0x150 ? 1 : -1];
typedef char ManagedSlotEvents[(u32) & ((Recovered_ManagedSlot*)0)->events == 0x6F0 ? 1 : -1];
typedef char ManagedSlotQuery[(u32) & ((Recovered_ManagedSlot*)0)->query == 0xC94 ? 1 : -1];
typedef char ManagerSlots[(u32) & ((Recovered_AIManager*)0)->slots == 0x2B00 ? 1 : -1];
typedef char ManagerRandom[(u32) & ((Recovered_AIManager*)0)->random == 0x22BC0 ? 1 : -1];

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
#endif
