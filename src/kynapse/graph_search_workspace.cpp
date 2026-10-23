#include "campaign/graph/search_workspace.hpp"

namespace KaimSearch {
void FreeSearch()
{
    if (gOpenList)
        delete gOpenList;
    if (gClosedList)
        delete gClosedList;
    if (gOpenHandles)
        delete[] gOpenHandles;
    if (gClosedHandles)
        delete[] gClosedHandles;
    if (gCostSoFar)
        D_003C87E0(gCostSoFar);
    if (gScore)
        D_003C87E0(gScore);
    gSearchCapacity = 0;
    gOpenList = 0;
    gClosedList = 0;
    gOpenHandles = 0;
    gClosedHandles = 0;
    gCostSoFar = 0;
    gScore = 0;
}

// Sizes the search lists and score tables for `capacity` nodes.
bool InitSearch(unsigned int capacity)
{
    gRelaxCount = 0;
    FreeSearch();
    if (capacity > 0) {
        gSearchCapacity = capacity;
        gOpenList = new SearchList(gSearchCapacity);
        gClosedList = new SearchList(gSearchCapacity);
        gOpenHandles = new NodeCursor[gSearchCapacity];
        gClosedHandles = new NodeCursor[gSearchCapacity];
        gCostSoFar = (float*)Allocate(gSearchCapacity << 2);
        gScore = (float*)Allocate(gSearchCapacity << 2);
    } else {
        gSearchCapacity=0;
        gOpenList = 0;
        gClosedList = 0;
        gOpenHandles = 0;
        gClosedHandles = 0;
        gCostSoFar = 0;
        gScore = 0;
    }
    gProfileIndex = ((NameTableC*)GetNameTables())->FindName("AstarLoop");
    return true;
}


// Unmatched: predecessor helper and vector temporary register allocation.
#if 0
bool SearchGraph::ReconstructRoute(SearchRoute* route, GraphNode* goal)
{
    unsigned int start = gSearchStart;
    route->graph = this;
    int steps = 0;
    GraphNode* node = goal;
    if (node->id != start) {
        do {
            SearchEdge* edge = PredecessorOf(node);
            node = edge->EndNode();
            ++steps;
            if ((int)liveNodes <= steps) {
                route->count = 0;
                return false;
            }
            start = gSearchStart;
        } while (node->id != gSearchStart);
    }
    unsigned int capacity = route->capacity;
    if ((int)capacity < steps + 1) {
        route->truncated = true;
        route->count = capacity;
    } else {
        route->truncated = false;
        route->count = steps + 1;
    }
    unsigned int count = route->count;
    if (count != 0 && count <= capacity) {
        route->nodeIds[count - 1] = goal->id;
        route->edgeIds[route->count - 1] = 0xffffffff;
        route->positions[route->count-1]=*(SearchPosition*)&goal->x;
        route->guards[route->count - 1] = 0;
    }
    if ((int)route->capacity < steps) {
        do {
            if (goal->id == start)
                goto finished;
            SearchEdge* edge = PredecessorOf(goal);
            route->length = route->length + edge->GetAuthoredLength();
            goal = edge->EndNode();
            --steps;
        } while ((int)route->capacity < steps);
    }
    if (goal->id != start) {
        int positionIndex = steps * 3;
        int slot = steps;
        do {
            route->nodeIds[slot - 1] = PredecessorOf(goal)->EndNode()->id;
            route->edgeIds[slot - 1] = PredecessorOf(goal)->index;
            route->guards[slot-1]=PredecessorOf(goal)->Guard();
            GraphNode* previous = PredecessorOf(goal)->EndNode();
            route->positions[slot-1]=*(SearchPosition*)&previous->x;
            goal = PredecessorOf(goal)->EndNode();
            --slot;
            positionIndex -= 3;
        } while (goal->id != gSearchStart);
    }
finished:
    gSearchStart = 0xffffffff;
    gSearchFlag = 0;
    return true;
}
#endif


// Unmatched: C++ iterator return temporaries and inlining.
#if 0
NodeCursor InsertByScore(SearchList *list,GraphNode *node) {
    NodeCursor before=list->Begin();
    while(before.IsValid()) {
        if(gScore[node->id]<gScore[before.Get()->id])break;
        ++before;
    }
    return list->Insert(node,before);
}
#endif

// Resets the per-node search tables of the live nodes.
static inline void ClearSearchTables(SearchGraph *graph) {
    gClosedList->Clear();gOpenList->Clear();
    int remaining=graph->liveNodes;
    unsigned int slot=0;
    if(remaining) {
        do {
            GraphNode *node=0;
            if(slot<graph->nodeCapacity){GraphNode *candidate=graph->nodes+slot;if(candidate->id!=(unsigned int)-1)node=candidate;}
            if(node){--remaining;gOpenHandles[node->id]=NodeCursor(0);gClosedHandles[node->id]=NodeCursor(0);}
            ++slot;
        }while(remaining);
    }
}

inline bool RelaxVisitor::EnumerateOutgoingEdges(GraphNode* node)
{
    Begin(node);
    SearchEdge* edge = node->GetOutgoing(0);
    unsigned int* links = node->graph->outgoingNext;
    if (links) {
        if (edge) {
            while (edge->EndNode() == node) {
                if (!Relax(edge)) return false;
                unsigned int next = links[edge->index];
                if (node->graph->edgeCapacity <= next) break;
                edge = &node->graph->edges[next];
                if (edge->index == -1 || !edge) break;
            }
        }
    } else {
        unsigned int ordinal = 0;
        if (edge) {
            do {
                if (!Relax(edge)) return false;
                ++ordinal;
                edge = node->GetOutgoing(ordinal);
            } while (edge);
        }
    }
    return true;
}
// Unmatched: outgoing helper inlining and visitor register allocation.
#if 0
void SearchGraph::Expand(GraphNode *node,GraphNode *goal,GraphNode *start,void *context) {
    RelaxVisitor visitor;
    visitor.current=node;visitor.goal=goal;visitor.start=start;visitor.graph=this;visitor.context=context;
    visitor.EnumerateOutgoingEdges(node);
}
#endif


// Unmatched: cursor temporaries and node traversal register allocation.
#if 0
bool SearchGraph::FindRoute(SearchRoute* route, GraphNode* start, GraphNode* goal, void* context)
{
    unsigned int graphFlags = flags;
    if (!(graphFlags & 1))
        return false;
    if (!heuristic)
        return false;
    if (!costPolicy)
        return false;
    if ((graphFlags & 0x10) && !goal->GetIncoming(0))
        return false;
    if ((graphFlags & 8) && !start->GetOutgoing(0))
        return false;
    ClearSearchTables(this);
    gCostSoFar[start->id] = 0;
    float estimate;
    if (!heuristic->Estimate(context, start, goal, &estimate))
        return false;
    gScore[start->id] = estimate + gCostSoFar[start->id];
    unsigned int startId = start->id;
    gSearchStart = startId;
    SearchList* open = gOpenList;
    gOpenHandles[startId]=InsertByScore(open,start);
    while (open->Begin().IsValid()) {
        GraphNode* current = open->Begin().Get();
        if (current->id == goal->id)
            return ReconstructRoute(route, goal);
        Expand(current,goal,start,context);
        open = gOpenList;
        open->Remove(*reinterpret_cast<const NodeCursor*>(gOpenHandles + current->id));
        gOpenHandles[current->id]=NodeCursor(0);
        unsigned int currentId = current->id;
        gClosedHandles[currentId]=InsertByScore(gClosedList,current);
    }
    gSearchStart = 0xffffffff;
    return false;
}
#endif

// Folds a finished burst of expansions into the running mean and deviation.
static __forceinline void PublishStatistics(unsigned int* samples, float* mean, float* deviation, int burst, float elapsed)
{
    float total = (float)(*samples + burst);
    float count = (float)*samples;
    float newMean = (count * *mean + elapsed) / total;
    *mean = newMean;
    *deviation = (count * *deviation + fabsf((float)burst * newMean - elapsed)) / total;
    *samples = *samples + burst;
}


// Unmatched: timed state-machine and cursor lifetimes.
#if 0
unsigned int SearchGraph::AdvanceTimed(SearchRoute* route, GraphNode* start, GraphNode* goal, void* context,
                                       unsigned int* samples, float* mean, float* deviation,
                                       float deviationScale, float budget, unsigned int restart)
{
    if (!(flags & 1) || !heuristic || !costPolicy)
        return 0;
    float remaining = budget;
    float begin = gSearchClock ? gSearchClock() : 0.0f;
    float burstLimit = 1.0f;
    float expected = *mean + deviationScale * *deviation;
    if (expected != 0.0f)
        burstLimit = budget / expected;
    SearchList* open = gOpenList;
    if (!restart) {
        if (!gTimedActive) {
            if (gTimedStart == start) {
                if (gSavedStart != start || gSavedGoal != goal || gSavedContext != context ||
                    gSavedHeuristic != heuristic || gSavedCost != costPolicy) gTimedActive=1;
            } else {gSearchStart=(unsigned int)-1;gTimedActive=1;}
        }
    }else gTimedActive=1;
    if(gTimedActive==1) {
    ClearSearchTables(this);
    gCostSoFar[start->id] = 0;
    {
        float estimate;
        if (!heuristic->Estimate(context, start, goal, &estimate))
            return 0;
        open = gOpenList;
        gScore[start->id] = estimate;
        unsigned int startId = start->id;
        gTimedStart = start;
        gSearchStart = startId;
        gOpenHandles[startId]=InsertByScore(open,start);
    }
    }
    for (;;) {
        int burst = 0;
        do {
            if (!open->head) {
                gSearchStart = 0xffffffff;
                gTimedActive = 1;
                gTimedStart = 0;
                return 0;
            }
            GraphNode* current = open->head->value;
            if (current->id == goal->id) {
                gTimedActive = ReconstructRoute(route, goal) ? 1 : 0;
                float now = gSearchClock ? gSearchClock() : 0.0f;
                PublishStatistics(samples, mean, deviation, burst, now - begin);
                return gTimedActive != 0;
            }
            Expand(current,goal,start,context);
            open = gOpenList;
            open->Remove(*reinterpret_cast<const NodeCursor*>(gOpenHandles + current->id));
            gOpenHandles[current->id]=NodeCursor(0);
            unsigned int currentId = current->id;
            gClosedHandles[currentId]=InsertByScore(gClosedList,current);
            ++burst;
        } while ((float)(unsigned int)burst < burstLimit);
        float now = gSearchClock ? gSearchClock() : 0.0f;
        float elapsed = now - begin;
        if (remaining <= elapsed) {
            PublishStatistics(samples, mean, deviation, burst, elapsed);
            gTimedActive = 0;
            gSavedStart = start;
            gSavedGoal = goal;
            gSavedContext = context;
            gSavedHeuristic = heuristic;
            gSavedCost = costPolicy;
            return 2;
        }
        PublishStatistics(samples, mean, deviation, burst, elapsed);
        burstLimit = 1.0f;
        expected = *mean + deviationScale * *deviation;
        if (expected != 0.0f)
            burstLimit = (remaining - elapsed) / expected;
        begin = now;
        remaining = remaining - elapsed;
    }
}
#endif

}  // namespace Kaim
