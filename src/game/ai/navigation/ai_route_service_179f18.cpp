#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_route_service_decls.hpp"

namespace Game {
// /SLUS_213.76 0x179f18
// Unmatched: PS2 distance is VU0 macro code (vsqrt); the Xbox returns it in XMM0.

float EndpointDistance(const RouteRequest* request)
{
    Vec from = Load(request->origin);
    Vec to = Load(request->destination);
    return Length3(Sub3(to, from));
}

// /SLUS_213.76 0x179f60
// Unmatched: private register contract (request in EAX, destination view in EDX).
void BorrowStorage(const RouteRequest* request, RouteStorage* into)
{
    into->graph = request->storage->graph;
    into->count = request->storage->count;
    into->nodeIds = request->storage->nodeIds;
    into->links = request->storage->links;
    into->points = request->storage->points;
    into->edgeData = request->storage->edgeData;
    into->unknown1c = request->storage->unknown1c;
    into->field20 = request->storage->field20;
    into->field24 = request->storage->field24;
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/ai_route_service_179f18", func_00179FD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/navigation/ai_route_service_179f18", func_0017A008);
