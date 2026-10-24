#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x179ed0
// PS2 0x179ed0; the Xbox build expands it inside RouteMode::Recover.

void RouteRequest::Resubmit(PositionArg from)
{
    SubmitRouteRequest(this, from, Load(destination), reuse);
}

// /SLUS_213.76 0x179ef0
// PS2 0x179ef0; the Xbox build expands it (ai_movement.hpp) where requests are released.
void RouteRequest::Release()
{
    storage->graph = 0;
    storage->count = 0;
    busy = 0;
    firstPoint = 0;
    kind = 0;
    result = 0;
}

}  // namespace BlackGame
