#include "include_asm.h"
#include "game/actor_slots.h"

extern s32 func_0018DDD8(void* query);
extern void func_0013D7A0(Recovered_ManagedSlot* slot, s32 index);
extern void func_001699A8(void* service, Recovered_ManagedActor* actor);
extern Recovered_AIManager* D_0040F4D4;
extern void* D_0040F4F4;

s32 ActorSlot_IsState0(Recovered_ActorSlot* entry) { return entry->state == 0; }

#ifdef NON_MATCHING
// Unmatched: boolean normalization and saved-register copy differ.
s32 ActorSlot_HasActiveQuery(Recovered_ActorSlot* entry) {
    s32 active = 0;
    if (entry->state == 0) {
        if (Actor_GetManagedSlot(entry->actor)) {
            if (Actor_GetManagedSlot(entry->actor)->unk_80 == 1) {
                active = func_0018DDD8(Actor_GetManagedSlot(entry->actor)->query) != 0;
            }
        }
    }
    return active;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_178f18", func_00178F50);
#endif

s32 ActorSlot_IsState3(Recovered_ActorSlot* entry) { return entry->state == 3; }
s32 ActorSlot_IsState0Or3(Recovered_ActorSlot* entry) {
    s32 result = 0;
    if (entry->state == 0 || entry->state == 3) result = 1;
    return result;
}
u32 ActorSlot_Mask(Recovered_ActorSlot* entry) { return 1U << entry->index; }
void func_00179010(void) {}

s32 ActorSlotTable_Reset(Recovered_ActorSlotTable* table) {
    s32 index = 0;
    s32 unusedState = 5;
    Recovered_ActorSlot* entry = table->entries;
    for (; index < 32; ++index, ++entry) {
        entry->index = index;
        entry->state = unusedState;
    }
    table->occupied = 0;
    return 1;
}
void func_00179050(void) {}
s32 func_00179058(void) { return 1; }

s32 ActorSlotTable_AddState0(Recovered_ActorSlotTable* table, Recovered_ManagedActor* actor) {
    s32 index = ActorSlotTable_FindFree(table);
    if (index != -1) {
        table->occupied |= 1U << index;
        table->entries[index].state = 0;
        table->entries[index].actor = actor;
        return index;
    }
    return -1;
}
s32 ActorSlotTable_AddState1(Recovered_ActorSlotTable* table, Recovered_ManagedActor* actor) {
    s32 index = ActorSlotTable_FindFree(table);
    if (index != -1) {
        table->occupied |= 1U << index;
        table->entries[index].state = 1;
        table->entries[index].actor = actor;
        return index;
    }
    return -1;
}
s32 ActorSlotTable_AddState2Or3(Recovered_ActorSlotTable* table, Recovered_ManagedActor* actor, s32 state3) {
    s32 index = ActorSlotTable_FindFree(table);
    if (index == -1) return -1;
    {
        table->occupied |= 1U << index;
        if (state3)
            table->entries[index].state = 3;
        else
            table->entries[index].state = 2;
        table->entries[index].actor = actor;
        return index;
    }
}
void ActorSlotTable_Remove(Recovered_ActorSlotTable* table, s32 index) {
    ActorSlotTable_NotifyRemoval(table, index);
    table->entries[index].state = 5;
    table->occupied &= ~(1U << index);
}
s32 ActorSlotTable_Contains(Recovered_ActorSlotTable* table, s32 index) {
    u32 mask = 1U << index;
    return (mask & table->occupied) == mask;
}
Recovered_ActorSlot* ActorSlotTable_GetEntry(Recovered_ActorSlotTable* table, s32 index) {
    return (Recovered_ActorSlot*)((void*)table + (index * 12 + 4));
}
s32 ActorSlotTable_FindFree(Recovered_ActorSlotTable* table) {
    s32 index;
    for (index = 0; index < 32; ++index) {
        if (!(table->occupied & (1U << index))) return index;
    }
    return -1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_178f18", func_001792A8);

s32 ActorSlotTable_FindState0Actor(Recovered_ActorSlotTable* table, Recovered_ManagedActor* actor) {
    s32 index;
    for (index = 0; index < 32; ++index) {
        if (table->entries[index].state == 0 && table->entries[index].actor == actor) return index;
    }
    return -1;
}
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_178f18", func_001792F0);

#ifdef NON_MATCHING
// Unmatched: loop counter and slot-offset registers differ.
void ActorSlotTable_NotifyRemoval(Recovered_ActorSlotTable* table, s32 index) {
    s32 slotOffset;
    s32 activeOffset;
    s32 remaining;
    remaining = 15;
    activeOffset = 0;
    slotOffset = (u32) & ((Recovered_AIManager*)0)->slots;
    do {
        Recovered_AIManager* manager = D_0040F4D4;
        u8* active = (u8*)(activeOffset + (u32)manager) + (u32) & ((Recovered_AIManager*)0)->slots[0].active;
        if (*active) func_0013D7A0((Recovered_ManagedSlot*)((u32)manager + slotOffset), index);
        --remaining;
        slotOffset += sizeof(Recovered_ManagedSlot);
        activeOffset += sizeof(Recovered_ManagedSlot);
    } while (remaining >= 0);
    if (ActorSlot_IsState0(ActorSlotTable_GetEntry(table, index))) {
        func_001699A8(D_0040F4F4, ActorSlotTable_GetEntry(table, index)->actor);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_178f18", func_00179300);
#endif
