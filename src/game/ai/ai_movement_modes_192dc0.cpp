#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
// /SLUS_213.76 0x192dc0
// Unmatched: private register contract (mode in EDI) and inlined resubmit expansion.

bool RouteMode::Recover()
{
    if (resubmit) {
        if (alternate) { alternate->Release(); alternate = 0; }
        resubmit = 0;
    }
    if (active && state != 8 && state != 0) {
        active->Resubmit(Load(brain->actor->position));
        state = ClassifyRouteResult(active);
        return true;
    }
    return false;
}

// /SLUS_213.76 0x192e50
void RouteMode::Stop()
{
    MovementModeBase::Stop();
    if (active) { active->Release(); active = 0; }
    if (alternate) { alternate->Release(); alternate = 0; }
    resubmit = 0;
    arrived = 0;
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/ai_movement_modes_192dc0", func_00192EB0);
