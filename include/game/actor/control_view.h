#ifndef GAME_ACTOR_CONTROL_VIEW_H
#define GAME_ACTOR_CONTROL_VIEW_H
#include "game/ai_manager.h"

/* Partial native body view. UNVERIFIED: the vector-query consumer remains a
 * draft; unaccessed bytes and the total component extent remain unknown. */
typedef struct {
    u8 unk_00[0x3C];
    u8 vectorActive;
} Recovered_ActorBodyState;

/* UNVERIFIED until a source-exact caller confirms this view. Native callers
 * supply an integer kind, full-quad payload and FPR weight; the virtual result
 * is unused. The original method and enclosing class identities are unknown. */
struct Recovered_ManagedSlotDispatch {
    u8 unk_00[0x28];
    s16 vectorEventAdjustment;
    u16 unk_2A;
    void (*vectorEvent)(void*, s32, s128, f32, s32);
};

/* The native indexed pointer table begins at +0x25c. Its extent is unknown. */
static inline void** Actor_IndexedControls(Recovered_ManagedActor* actor) {
    return (void**)((u8*)actor + 0x25C);
}
#endif
