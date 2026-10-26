#ifndef GAME_AI_ACTOR_SLOT_VALUES_H
#define GAME_AI_ACTOR_SLOT_VALUES_H
#include "game/actor_slots.h"
#include "game/actor_binding.h"

/* The slot payload at +8 is selected by state: actor (0), binding (1),
 * indirect actor (2), or a point pointer (3). Other state meanings are unknown. */
typedef struct {
    u8 unk_00[0x10];
    Recovered_ManagedActor* actor;
} Recovered_ActorSlotIndirect;

typedef struct {
    u8 unk_00[0x18];
    const s128* position;
} Recovered_ActorSlotPositionGroup;

/* UNVERIFIED: these views come from unfinished value getters. Unaccessed byte
 * spans, original class identities and complete object extents remain unknown. */
static inline Recovered_ActorSlotPositionGroup** ActorSlot_PositionGroups(Recovered_AIManager* manager) {
    /* Native table base; its number of entries is unknown. */
    return (Recovered_ActorSlotPositionGroup**)((u8*)manager + 0x22B20);
}

static inline const s128* ActorSlot_ActorVector(Recovered_ManagedActor* actor) {
    /* UNVERIFIED: only this address is observed; vector role and storage width are unknown. */
    return (const s128*)((u8*)actor + 0xF0);
}

const s128* func_00178D30(Recovered_ActorSlot* entry);
const s128* func_00178DE0(Recovered_ActorSlot* entry);
s128 func_00178E60(Recovered_ActorSlot* entry);
#endif
