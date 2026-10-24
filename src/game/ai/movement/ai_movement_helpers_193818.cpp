#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_helpers_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x193818

void FormationMode::ContinueToGoal()
{
    PositionArg goal = FormationGoalPoint(&brain->formation);
    bool arrived = !RequestDestinationMotion(brain->controller.speed, this, goal, true, 0.1f);
    if (arrived) state = 8;
}

}  // namespace BlackGame
