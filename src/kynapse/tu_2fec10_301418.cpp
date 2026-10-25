#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/pathfinder.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: remaining class-call context, lifetime or scheduling differences.
bool CPathFinder::RefreshSearch(bool invalidateStart, bool* changed, RouteRequest* request)
{
    void* start = collectNode(this, &position.x, 1, 0);
    void* goal = 0;
    if (request)
        goal = ResolveRequestNode(request);
    if (!goal)
        goal = collectNode(this, &target.x, 0, 1);
    if (!searchPaused && (!invalidateStart || start == startNode) && goal == goalNode && !restartSearch) {
        *changed = false;
        return searchOk;
    }
    *changed = true;
    startNode = start;
    goalNode = goal;
    if (!start || !goal)
        return false;
    RouteBlock* route = (RouteBlock*)((char*)this + 0x6c);
    route->count = 0;
    route->length = 0;
    if (routeTable) {
        if (source->GetType() == &gRouteTableType)
            return routeTable->Build(*(unsigned int*)startNode, *(unsigned int*)goalNode, route);
    }
    graph->costPolicy = GetCostPolicy();
    graph->heuristic = GetHeuristic();
    if (!avoidCpuPeaks)
        return graph->FindRoute(route, startNode, goalNode, controller->actor);
    SearchRecord* record = &records[*(int*)((char*)source->GetType() + 4)];
    float remaining = GetNameTables()->Remaining(searchSlotIndex);
    if (remaining < 0.0005f)
        remaining = 0.0005f;
    searchPaused = false;
    unsigned int status = graph->AdvanceTimed(route, startNode, goalNode, controller->actor, &record->samples,
                                              &record->mean, &record->deviation, record->scale, remaining,
                                              restartSearch);
    if (status == 0)
        return false;
    if (status == 1)
        return true;
    if (status == 2) {
        searchPaused = true;
        GetNameTables()->SelectUser(controller->actor);
        return true;
    }
    return false;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2fec10_301418", func_00301418);
#endif
