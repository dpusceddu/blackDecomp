#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
// /SLUS_213.76 0x192a00
// PS2 0x192a00; the Xbox build expands the dispatch inside RouteMode::Update.

bool RouteMode::StepPhase()
{
    switch (state) {
    case 7: return ResolveSubmitted();
    case 1: return ResolveCurrent();
    case 4: return FollowCurrentDestination(this);
    }
    return false;
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/ai_movement_modes_192a00", func_00192A78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/ai_movement_modes_192a00", func_00192D48);
