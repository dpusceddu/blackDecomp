#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x17a9c8
// Unmatched: private register contract for the stored __m128 argument.

bool RouteRequest::UpdateDestination(PositionArg point)
{
    if (kind == 1 || kind == 3) {
        Store(destination, point);
        return true;
    }
    return false;
}

}  // namespace BlackGame
