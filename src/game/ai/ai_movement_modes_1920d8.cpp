#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_movement_modes_decls.hpp"

namespace Game {
// /SLUS_213.76 0x1920d8
// Unmatched: private register contract and inlined submit/release expansion.

void RouteMode::Start(PositionArg point)
{
    SetDestination(point);
    ReleaseMovementRoute(this);
    active = &requests[0];
    state = 7;
    SubmitRouteRequest(&requests[0], Load(brain->actor->position), point, true);
}

// /SLUS_213.76 0x192140
// Unmatched: private register contract and inlined submit/release expansion.
void RouteMode::Retarget(PositionArg point)
{
    if (!active) Start(point);
    MovementModeBase::Retarget(point);
    if (alternate) { alternate->Release(); alternate = 0; }
    if (active == &requests[0]) alternate = &requests[1];
    else alternate = &requests[0];
    SubmitRouteRequest(alternate, Load(target), point, true);
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001921D8);
