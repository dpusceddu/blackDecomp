#ifndef GAME_ACTOR_CONTROL_VIEW_H
#define GAME_ACTOR_CONTROL_VIEW_H
#include "game/ai_manager.h"

/* Partial native body view. UNVERIFIED: the vector-query consumer remains a
 * draft; unaccessed bytes and the total component extent remain unknown. */
typedef struct {
    u8 unk_00[0x3C];
    u8 vectorActive;
} Recovered_ActorBodyState;

/* Source-confirmed dispatch view: integer kind, full-quad payload and FPR
 * weight. The native return type remains UNVERIFIED because the result is unused.
 * Original method/class identities, unaccessed entries and full table extent
 * remain unknown. */
struct Recovered_ManagedSlotDispatch {
    u8 unk_00[0x28];
    s16 vectorEventAdjustment;
    u16 unk_2A;
    void (*vectorEvent)(void*, s32, s128, f32, s32);
};

/* Exact 0x1374f8/0x137520 confirm the 0x60 record stride, scalar at +0x4c
 * and accessed table/component pointers. UNVERIFIED: unaccessed spans, original
 * identities, gameplay roles and complete table/component extents. */
typedef struct {
    u8 unk_00[0x4C];
    f32 unk_4C;
    u8 unk_50[0x10];
} Recovered_ActorIndexedControl;

typedef struct {
    u8 unk_00[0x30];
    Recovered_ActorIndexedControl* records;
} Recovered_ActorIndexedTable;

typedef struct Recovered_ActorIndexedComponent {
    u8 unk_00[0x40];
    Recovered_ActorIndexedTable* controls;
} Recovered_ActorIndexedComponent;

static inline Recovered_ActorIndexedControl* Actor_IndexedRecord(Recovered_ManagedActor* actor, s32 index) {
    return actor->unk_BC->controls->records + (u16)index;
}

typedef char ActorIndexedControlStride[sizeof(Recovered_ActorIndexedControl) == 0x60 ? 1 : -1];
typedef char ActorIndexedControl4C[(u32)&((Recovered_ActorIndexedControl*)0)->unk_4C == 0x4C ? 1 : -1];

/* The native indexed pointer table begins at +0x25c. Its extent is unknown. */
static inline void** Actor_IndexedControls(Recovered_ManagedActor* actor) {
    return (void**)((u8*)actor + 0x25C);
}
/* UNVERIFIED: native selector +0x19 and table base +0x0c, shared with the
 * animation selector's existing HasLayer access. Full table extent is unknown. */
static inline u8 Actor_LayerHasEntry(Recovered_ManagedActor* actor) {
    u8* layer = (u8*)actor->unk_26C;
    u8 found = 0;
    if (layer) found = *(void**)(layer + 0xC + 4 * layer[0x19]) != NULL;
    return found;
}
#endif
