#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
// /SLUS_213.76 0x191c18

bool MovementModeBase::UpdateTarget(PositionArg) { return false; }

// /SLUS_213.76 0x191c20
void RouteMode::Bind(Brain* owner)
{
    BindBase(owner);
    follower = 0;
}

}  // namespace Game
