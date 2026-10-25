#include "include_asm.h"

#define BLACK_PS2 1
#include "game/ai_movement_modes_decls.hpp"
namespace Game {

bool RouteMode::UpdateTarget(PositionArg point)
{
    switch (state) {
    case 0: case 2: case 3: case 6: case 8: return false;
    case 1: case 7:
        return active->UpdateDestination(point);
    case 4: case 5:
        if (arrived) return false;
        if (active->busy) return active->UpdateDestination(point);
        return RetargetLive(this, point);
    }
    return false;
}
}

// Unmatched: 00191C80 reset retains follower interface and allocation differences.
// Unmatched: 001930F8 route join retains27 iterator/register and vector lifetime differences.
