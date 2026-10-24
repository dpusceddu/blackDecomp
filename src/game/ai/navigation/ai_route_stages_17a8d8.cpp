#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_route_stages_decls.hpp"

namespace BlackGame {
// /SLUS_213.76 0x17a8d8
// Stage 7: probes the controller's local route from the origin to the next stored point (unlifted);
// finishes the request, and consumes that point when the probe is clear.
// Unmatched: Xbox request in EDI with packed-vector temporaries; PS2 vector math.

bool CheckFinalRouteLeg(RouteRequest* request)
{
    bool clear = CheckLocalRoute(&request->owner->controller, Load(request->origin),
                                 UnliftedPoint(request->storage->points[request->firstPoint + 1]));
    if (clear) request->SkipPoint();
    request->kind = 9;
    return true;
}

// /SLUS_213.76 0x17a980
// PS2 0x17a980; the Xbox build expands it.
void RouteRequest::SkipPoint() { firstPoint++; }

// /SLUS_213.76 0x17a990
// PS2 0x17a990; the Xbox build expands it.
// Drops the final route point and terminates the link list there.
void RouteRequest::DropFinalPoint()
{
    storage->count--;
    storage->links[storage->count] = 0xffffffffu;
}

}  // namespace BlackGame
