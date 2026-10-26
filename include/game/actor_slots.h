#ifndef GAME_ACTOR_SLOTS_H
#define GAME_ACTOR_SLOTS_H
#include "game/ai_manager.h"

/* State numbers are native values; their broader gameplay meanings remain open.
 * Indexed operations require an index from 0 through 31. Reset retains actor pointers. */
typedef struct {
    s32 index;
    s32 state;
    Recovered_ManagedActor* actor;
} Recovered_ActorSlot;
typedef struct {
    u32 occupied;
    Recovered_ActorSlot entries[32];
} Recovered_ActorSlotTable;
typedef char ActorSlotStride[sizeof(Recovered_ActorSlot) == 12 ? 1 : -1];
typedef char ActorSlotTableSize[sizeof(Recovered_ActorSlotTable) == 0x184 ? 1 : -1];

#ifdef __cplusplus
extern "C" {
#endif

s32 ActorSlot_IsState0(Recovered_ActorSlot* entry);
s32 ActorSlot_HasActiveQuery(Recovered_ActorSlot* entry);
s32 ActorSlot_IsState3(Recovered_ActorSlot* entry);
s32 ActorSlot_IsState0Or3(Recovered_ActorSlot* entry);
u32 ActorSlot_Mask(Recovered_ActorSlot* entry);
s32 ActorSlotTable_Reset(Recovered_ActorSlotTable* table);
s32 ActorSlotTable_AddState0(Recovered_ActorSlotTable* table, Recovered_ManagedActor* actor);
s32 ActorSlotTable_AddState1(Recovered_ActorSlotTable* table, Recovered_ManagedActor* actor);
s32 ActorSlotTable_AddState2Or3(Recovered_ActorSlotTable* table, Recovered_ManagedActor* actor, s32 state3);
void ActorSlotTable_Remove(Recovered_ActorSlotTable* table, s32 index);
s32 ActorSlotTable_Contains(Recovered_ActorSlotTable* table, s32 index);
Recovered_ActorSlot* ActorSlotTable_GetEntry(Recovered_ActorSlotTable* table, s32 index);
s32 ActorSlotTable_FindFree(Recovered_ActorSlotTable* table);
s32 ActorSlotTable_FindState0Actor(Recovered_ActorSlotTable* table, Recovered_ManagedActor* actor);
void ActorSlotTable_NotifyRemoval(Recovered_ActorSlotTable* table, s32 index);
/* The gameplay meaning of native actor category 2 remains unknown. */
s32 ActorSlot_IsState0Kind2(Recovered_ActorSlot* entry);
#ifdef __cplusplus
}
#endif
#endif
