// Ported from the companion project (an unpublished companion project), PS2 branches only.
#include "game/ai_route_service_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x179ce0
// Unmatched: PS2 vector subtraction is VU0 macro code; the Xbox passes the result through EAX.
PositionResult RoutePointAt(const RouteRequest* request, int index)
{
    return Sub3(WidenVec(request->storage->points[index]), Load(gRouteLift));
}

// /SLUS_213.76 0x179d40
Point3* RoutePointAddress(const RouteRequest* request, int index)
{
    return &request->storage->points[index];
}

}  // namespace BlackGame
