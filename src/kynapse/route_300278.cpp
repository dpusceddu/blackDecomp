#include "include_asm.h"

#include "kynapse/ai_route_follower.hpp"

static inline void* PS2NodeAt(NavigationGraph* graph,unsigned int ordinal)
{
    if (ordinal>=graph->nodeCapacity) return 0;
    NavigationGraph::NodeRecord* node = (NavigationGraph::NodeRecord*)(ordinal * 20 + (unsigned int)graph->nodes);
    return node->id == -1 ? 0 : node;
}

void* AIRouteFollower::ResolveRequestNode(RouteRequest* request)
{
    RouteRequest* original = request;
    unsigned int ordinal;
    int graphValue;
    unsigned int converted;

    if (!converter)
        goto collect;
    if (graphId != (unsigned int)-1) {
        if (original->GetEndpoint(&ordinal, &graphValue)) {
            if (graphValue == graphId)
                return PS2NodeAt(graph,ordinal);
            if (converter->Convert(original, graphId, &converted))
                return PS2NodeAt(graph,converted);
        }
    }
collect:
    return collectNode(this, original->GetPoint(), 0, 0);
}

bool AIRouteFollower::IsDefaultCollector()
{
    if (collectNode == AIRouteFollower_CollectNodeLoose && !looseGraph)
        return false;
    return true;
}

bool AIRouteFollower::FollowPoint(const float* point, RouteRequest* request)
{
    activated = false;
    ((ActionBank*)world)->ClearActivation();
    Actor* actor = controller->actor;
    position = actor->position;
    movable = true;
    target = *(const Vec3f*)point;
    lastPoint = target;
    MoveRecord move;
    if (!FindNextMove(&move, request))
        return false;
    if (!activated && movable) {
        if (!Deliver(&move))
            return false;
    }
    return true;
}

bool __cdecl AIRouteFollower_ResetSegment(AIRouteFollower* follower, int* result)
{
    *result = 0;
    follower->previous = follower->position;
    follower->Stop();
    return true;
}

extern "C" unsigned int func_00305250(AIRouteFollower* follower, float* output,
                                                            const float* point)
{
    if (!follower->policy)
        return AIRouteFollower_GenerateMove(follower, output, point);
    follower->policy->Apply(point, output);
    return 1;
}

extern "C" void* func_00305378(AIRouteFollower* follower, const float* point,
                                               unsigned char outgoing, unsigned char incoming)
{
    if (!follower->looseGraph)
        return 0;
    return (void*)NavigationGraph_QueryNode(point, follower->controller->actor, follower->radius,
                                            follower->looseGraph, outgoing, incoming);
}



INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003003B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00300A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003016E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00301A30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00301E78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00302388);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00302EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003039D8);
