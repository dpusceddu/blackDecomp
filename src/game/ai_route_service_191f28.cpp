// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_route_service_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x191f28
// Resets the follower's route state and releases both requests.
// Unmatched: mode in ESI and request release expanded inline; 667 vs 657 bytes.
void ReleaseMovementRoute(RouteMode* mode)
{
    mode->follower->idle = 1;
    mode->follower->active = 0;
    Assign(mode->follower->graphOrigin, gUnsetPoint);
    Assign(mode->follower->point100, gUnsetPoint);
    Assign(mode->follower->endPosition, gUnsetPoint);
    Assign(mode->follower->routeEnd, gUnsetPoint);
    Assign(mode->follower->waypoint, gUnsetPoint);
    Assign(mode->follower->point10c, gUnsetPoint);
    Assign(mode->follower->routeEndCopy, gUnsetPoint);
    mode->follower->startNode = 0;
    mode->follower->endNode = 0;
    mode->follower->startNodeCopy = 0;
    mode->follower->endNodeCopy = 0;
    mode->follower->unknown1a8 = -1.0f;
    mode->follower->cursor = -1;
    ClearActivation(mode->follower->owner);
    if (mode->active) { mode->active->Release(); mode->active = 0; }
    if (mode->alternate) { mode->alternate->Release(); mode->alternate = 0; }
    mode->lastRoute = -1;
    mode->arrived = 0;
    mode->follower->stuck = 0;
    mode->resubmit = 0;
}

}  // namespace BlackGame
