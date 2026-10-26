#include "include_asm.h"
#include "game/ai/actor_slot_values.h"

extern Recovered_AIManager* D_0040F4D4;
extern const s128 D_004432A0;
extern const s128 D_004432B0;
extern const s128* func_00162570(Recovered_ActorBinding*);
/* Native actor +0x210 receiver; the component's class identity is unknown. */
extern s128 func_00173488(void*);


/* Actor-slot forwarding and value access. This file follows the existing
 * proposed split; the original source/TU identity remains unknown. */
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178408);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_001784F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_001785F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_001786B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178718);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178780);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_001787E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_001788A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/actor_slot_values", func_00178910);
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

/* The second vector has no storage for binding or direct-point slots. Its role is unknown. */
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

