#include "include_asm.h"

#include "kynapse/graph/tables.hpp"

Kaim::CAstarData::~CAstarData(){ if(rows){for(int i=0;i<count;++i)D_003C87E0(rows[i]);D_003C87E0(rows);} }

// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0

// Unmatched: stream-loading branch layout.
inline int LoadAstarResource(Kaim::CAstarData *data, ChildBuffers *config) {
 ChildBuffers *raw=func_002E31E0(config,"RawData");
 if(raw)return data->Load(raw);
 return false;
}

int Kaim::CAstarData::Init(ChildBuffers* config)
{
    int size = count;
    if (size > 0) {
        rows = (int**)Allocate(size * 4);
        for (int i = 0; i < count; ++i) {
            rows[i] = new int[count];
        }

    } else { rows = 0; return 0; }
        return LoadAstarResource(this,config);
    return false;
}

// Unmatched: route and allocator lifetimes, node/edge helper branch shape and register allocation.
int Kaim::CAstarData::Build()
{
    RouteBuffers route;
    route.Reserve(graph->liveNodes);
    DefaultHeuristic heuristic;
    DefaultCostPolicy policy;
    void* savedHeuristic = graph->heuristic;
    if (!savedHeuristic)
        graph->heuristic = &heuristic;
    void* savedPolicy = graph->costPolicy;
    if (!savedPolicy)
        graph->costPolicy = &policy;
    if (rows) {
        for (unsigned int i = 0; i < (unsigned int)graph->liveNodes; ++i)
            D_003C87E0(rows[i]);
        D_003C87E0(rows);
    }
    count = graph->liveNodes;
    if (count < 1) {
        rows = 0;
    } else {
        rows = new int *[count];
        for (int i = 0; i < count; ++i)
            rows[i] = new int[count];
    }
    for (int from = 0; from < count; ++from) {
        for (int to = 0; to < count; ++to) {
            if (from == to) {
                rows[from][to] = from;
                continue;
            }
            SearchNode *start = graph->GetNode(from);
            SearchNode *goal = graph->GetNode(to);
            route.Clear();
            if (!graph->FindRoute(&route, start, goal, 0)) {
                rows[from][to] = -1;
            } else { rows[from][to] = graph->GetEdge(route.edgeIds[0])->index; }
            if (progress)
                progress((count * from + to) * 100 / (count * count));
        }
    }
    graph->heuristic = savedHeuristic;
    graph->costPolicy = savedPolicy;
    return true;
}

// Unmatched: stream branch layout and loop scheduling.
extern const char D_00407950[],D_00407F08[];
extern const int D_00407968,D_00407F1C;

int Kaim::CAstarData::Save(const void* path)
{
    if (count < 1)
        return false;
    if (!rows)
        return false;
    void* file = D_00451228.open(path, "wb");
    if (file) {
        int version = D_00407F1C;
        if (D_00451228.write(D_00407F08, 1, func_0035CCD8(D_00407F08), file) == func_0035CCD8(D_00407F08) && D_00451228.write(&version, 4, 1, file) == 1) {
            int* buffer = 0;
            if (count > 0)
                buffer = (int*)Allocate(count * 4);
            for (int row = 0; row < count; ++row) {
                for (int i = 0; i < count; ++i)
                    buffer[i] = rows[row][i];
                D_00451228.write(buffer, 4, count, file);
            }
            if (buffer)
                D_003C87E0(buffer);
            D_00451228.close(file);
            return true;
        }
    }
    return false;
}

#endif

