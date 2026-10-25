#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_route_service_decls.hpp"

namespace Game {
// /SLUS_213.76 0x193040
// Moves the pending alternate request to a new destination, restarting it from the active
// request's end node when it can no longer be updated in place.
// Unmatched: Xbox takes the mode in EDI and the point in ECX; PS2 vector moves are VU0 macro code.

bool RetargetLive(RouteMode* mode, PositionArg point)
{
    if (!mode->alternate) mode->alternate = &mode->requests[1];
    if (!mode->alternate->UpdateDestination(point)) {
        if (IsSearching(mode->alternate->kind)) return false;
        SubmitRouteFromNode(mode->alternate, mode->active->endNode, point, 0);
    }
    mode->resubmit = 1;
    return true;
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001930F8);
