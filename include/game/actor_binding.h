#ifndef GAME_ACTOR_BINDING_H
#define GAME_ACTOR_BINDING_H
#include "game/ai_manager.h"

/* Partial native views; original class identities and complete sizes are unknown. */

typedef struct {
    u64 key;
    u8 unk_08[0x374];
    u32 generation;
    u8 unk_380[0xC];
    u32 invalid;
} Recovered_BoundActor;

typedef struct {
    u8 unk_00[0x10];
    s128 position; // UNVERIFIED: vector storage is used only by the position-sampling draft.
    u64 actorKey;
    f32 radius; // UNVERIFIED: position sampling remains a draft.
    s16 budget;
} Recovered_ActorBindingDescriptor;

typedef struct {
    u8 unk_00[0x10];
    s16 adjustment;
    u16 unk_12;
    void (*complete)(void*, Recovered_BoundActor*); // UNVERIFIED: original result contract is not observed.
} Recovered_ActorBindingMethods;

typedef struct {
    u8 unk_00[0x10];
    Recovered_ActorBindingMethods* methods;
    u8 unk_14[8];
    u8 active;
    u8 unk_1D[3];
    Recovered_BoundActor* current;
    Recovered_BoundActor* pending;
    s16 budget;
    u8 unk_2A[2];
    u32 generation;
    s32 registration;
    u8 unk_34[0xC];
    s128 position; // UNVERIFIED: only its address is returned in this TU.
    Recovered_ActorBindingDescriptor* descriptor;
} Recovered_ActorBinding;

typedef struct {
    u32 unk_00;
    s32 count;
    u32 unk_08;
    Recovered_BoundActor** entries;
} Recovered_BoundActorCatalog;

typedef struct {
    u8 unk_00[0x79A0];
    Recovered_BoundActorCatalog catalog;
} Recovered_ActorBindingCatalogServices;

typedef char BoundActorGenerationOffset[(u32) & ((Recovered_BoundActor*)0)->generation == 0x37C ? 1 : -1];
typedef char ActorBindingDescriptorOffset[(u32) & ((Recovered_ActorBinding*)0)->descriptor == 0x50 ? 1 : -1];
typedef char ActorBindingBudgetOffset[(u32) & ((Recovered_ActorBinding*)0)->budget == 0x28 ? 1 : -1];

void ActorBinding_UpdateCurrent(Recovered_ActorBinding* self);
Recovered_BoundActor* ActorBinding_FindCandidate(Recovered_ActorBinding* self);
s128 ActorBinding_SamplePosition(Recovered_ActorBinding* self);
void ActorBinding_DecrementBudget(Recovered_ActorBinding* self);
#endif
