// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_route_stages_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x1933f0
// Drops route points the follower already passed (keeping at least two) and republishes the
// follower's current waypoint.
// Unmatched: Xbox mode in ESI (private contract).
void TrimConsumedRoutePoints(RouteMode* mode)
{
    while (mode->follower->cursor > 1 && mode->active->PointCount() > 2) {
        RemoveFirstPoint(mode->active);
        mode->follower->cursor--;
    }
    Assign(mode->follower->waypoint, RoutePoint(mode->active, mode->follower->cursor));
}

}  // namespace BlackGame
