#include "include_asm.h"

// Ported from an unpublished companion project, PS2 branches only.
#include "game/ai_route_stages_decls.hpp"

namespace Game {
// /SLUS_213.76 0x17a320
// Stage 3: waits for the node search at the origin; a node ends the stage by starting the search
// at the destination, none fails the request (result 1).
// Unmatched: Xbox request in EDI (private contract).

bool CollectRouteStart(RouteRequest* request)
{
    if (!Manager()->nodeSearch.Advance()) return false;
    request->startNode = Manager()->nodeSearch.result;
    if (!request->startNode) {
        request->kind = 10;
        request->result = 1;
        return false;
    }
    request->kind = 4;
    Manager()->nodeSearch.Begin(Load(request->destination));
    return false;
}

// /SLUS_213.76 0x17a3a0
// Stage 4: waits for the destination node, tests the two nodes for connectivity for the actor's
// model family and then hands the request to the timed search with the owner's graph and policies.
// Unmatched: Xbox request in EDI (private contract).
bool CollectRouteGoal(RouteRequest* request)
{
    if (!Manager()->nodeSearch.Advance()) return false;
    request->endNode = Manager()->nodeSearch.result;
    if (!request->endNode) {
        request->kind = 10;
        request->result = 1;
        return false;
    }
    ModelRef model = ModelOf(request->owner->actor);
    if (!TestFamilyRoute(&Manager()->connectivity, request->startNode, request->endNode,
                         FamilyOf(model), 0x3f)) {
        request->kind = 10;
        request->result = 1;
        return false;
    }
    NavigationAgent* agent = request->owner->controller.navigator;
    request->storage->graph = agent->graph;
    agent->graph->cost = agent->CostPolicy();
    agent->graph->heuristic = agent->HeuristicPolicy();
    ResetSearchStatistics();
    request->kind = 5;
    return false;
}

// /SLUS_213.76 0x17a4a8
// Stage 5: advances the timed graph search. Found: validate and trim next; failed: result 1; paused
// searches accumulate frame time and fail with result 3 after 5 seconds. Only success steps again.
// Unmatched: Xbox request in EBX (private contract).
bool RunTimedRouteSearch(RouteRequest* request)
{
    switch (AdvancePathSearch(request->storage, request->startNode, request->endNode,
                              request->owner->actor->movement)) {
    case 0:
        request->result = 1;
        request->kind = 10;
        return false;
    case 2:
        request->elapsed += gGameClock->frameDelta;
        if (5.0f < request->elapsed) {
            request->kind = 10;
            request->result = 3;
        }
        return false;
    case 1:
        request->ValidateRoute();
        request->kind = 6;
        return true;
    }
    return false;
}

}  // namespace Game

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017A588);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0017A720);
