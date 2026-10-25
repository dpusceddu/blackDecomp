#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_route_stages_decls.hpp"

namespace Game {
// /SLUS_213.76 0x17a0a8
// Steps a request through its stage; false means wait until the next update. Kinds 0, 9 and 10
// have nothing to do.
// Unmatched: Xbox request in EAX and the stages are private callees (reproduced only under /GL).

bool AdvanceRouteRequest(RouteRequest* request)
{
    switch (request->kind) {
    case 1: return BeginQueuedRoute(request);
    case 2: return TryDirectRoute(request);
    case 3: return CollectRouteStart(request);
    case 4: return CollectRouteGoal(request);
    case 5: return RunTimedRouteSearch(request);
    case 7: return CheckFinalRouteLeg(request);
    case 6: return CompressRouteStart(request);
    case 8: return CompressRouteEnd(request);
    case 0: return false;
    case 9: return false;
    case 10: return false;
    }
    return false;
}

// /SLUS_213.76 0x17a170
// Stage 1: only the head of the queue may start searching. A reusable request goes straight to
// the local probe; otherwise the node search starts at the origin, or at the destination when the
// start node is already known.
// Unmatched (Xbox only): the request arrives in EDX and the contract is reproduced under /GL, but the
// original pushes EBX before the head comparison while the optimizer shrink-wraps it into the
// "start" path (reading the flag first moves the push but hoists the load, 24 bytes).
bool BeginQueuedRoute(RouteRequest* request)
{
    if (Manager()->routeQueue.Head() != request) {
        Manager()->routeQueue.Contains(request);
        return false;
    }
    if (request->reuse) {
        request->kind = 2;
    } else if (request->startNode) {
        request->kind = 4;
        Manager()->nodeSearch.Begin(Load(request->destination));
    } else {
        request->kind = 3;
        Manager()->nodeSearch.Begin(Load(request->origin));
    }
    return true;
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017A220);
