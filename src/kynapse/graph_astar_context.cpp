#include "include_asm.h"

#include "kynapse/graph/tables.hpp"
extern const char D_00407F08[];
extern const int D_00407F1C;
namespace Kaim {
extern unsigned int (*AstarRead)(void *, unsigned int, unsigned int, void *) __asm__("D_00451290");
extern "C" SearchNode *func_0038F2B0(const SearchEdge *);
extern "C" SearchNode *func_0038F2F0(const SearchEdge *);

inline SearchNode *SearchEdge::End() const {
    if (this == &graph->syntheticEdge)
        return (SearchNode *)&graph->syntheticEnd;
    return &graph->nodes[graph->ends[index]];
}
inline float SearchEdge::GeometricLength() const {
    if (this == &graph->syntheticEdge)
        return graph->syntheticGeometricLength;
    if (!graph->geometricLengths) {
        SearchNode *a = func_0038F2B0(this);
        SearchNode *b = func_0038F2F0(this);
        float dz = b->z-a->z, dx = b->x-a->x, dy = b->y-a->y;
        return sqrtf(dz*dz + dx*dx + dy*dy);
    }
    return graph->geometricLengths[index];
}
inline float SearchEdge::AuthoredCost() const {
    if (this == &graph->syntheticEdge)
        return graph->syntheticLength;
    if (!graph->edgeLengths)
        return 0;
    return graph->edgeLengths[index];
}
inline void *SearchEdge::Guard() const {
    if (this == &graph->syntheticEdge)
        return graph->syntheticGuard;
    if (!graph->edgeGuards)
        return 0;
    return graph->edgeGuards[index];
}
}

Kaim::CAstarData *CreateAstarData(Kaim::SearchGraph *graph) {
    return new Kaim::CAstarData(graph);
}


#ifdef NON_MATCHING
// Unmatched: matrix-allocation branch placement and inline loading scope.
int Kaim::CAstarData::Init(ChildBuffers *config) {
    if (count < 1) {
        rows = 0;
    } else {
        rows = new int *[count];
        for (int i = 0; i < count; ++i)
            rows[i] = new int[count];
        ChildBuffers *raw = func_002E31E0(config, "RawData");
        if (raw)
            return Load(raw);
    }
    return false;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FDA40);
#endif
#ifdef NON_MATCHING
// Unmatched: resource stream loop scheduling and inline native-word conversion.
bool Kaim::CAstarData::Load(const void *resource) {
    FileService *files = D_003C9ED4->files;
    if (!files || !files->Exists(resource))
        return false;
    char header[64];
    int version;
    unsigned int length = files->Read(resource, header, func_0035CCD8(D_00407F08));
    if (length == func_0035CCD8(D_00407F08) && files->Read(resource, &version, 4) == 4) {
        header[length] = 0;
        if (!func_00360838(D_00407F08, header) && version == 1) {
            for (int row = 0; row < count; ++row) {
                if (files->Read(resource, rows[row], count*4) != count*4)
                    goto fail;
                for (int col = 0; col < count; ++col)
                    rows[row][col] = rows[row][col];
            }
            files->Close(resource);
            return true;
        }
    }
fail:
    files->Close(resource);
    return false;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FDBA8);
#endif
#ifdef NON_MATCHING
// Unmatched: raw stream loop scheduling and header branch placement.
bool Kaim::CAstarData::LoadFile(const void *path) {
    void *file = D_00451228.open(path, "rb");
    if (file) {
        char header[64];
        int version;
        unsigned int n = AstarRead(header, 1, func_0035CCD8(D_00407F08), file);
        if (n == func_0035CCD8(D_00407F08) && AstarRead(&version, 4, 1, file) == 1) {
            header[n] = 0;
            if (!func_00360838(D_00407F08, header) && version == 1) {
                for (int row = 0; row < count; ++row) {
                    if (AstarRead(rows[row], 4, count, file) != count)
                        goto fail;
                    for (int col = 0; col < count; ++col)
                        rows[row][col] = rows[row][col];
                }
                D_00451228.close(file);
                return true;
            }
        }
fail:
        D_00451228.close(file);
    }
    return false;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FDD88);
#endif
#ifdef NON_MATCHING
// Unmatched: index-sentinel representation, route-result join and row cleanup scheduling.
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
    if (count > 0) {
        rows = new int *[count];
        for (int i = 0; i < count; ++i)
            rows[i] = new int[count];
    } else { rows = 0; }
    for (int from = 0; from < count; ++from) {
        for (int to = 0; to < count; ++to) {
            if (from == to) {
                rows[from][to] = from;
                continue;
            }
            SearchNode *start = graph->GetNode(from);
            SearchNode *goal = graph->GetNode(to);
            route.Clear();
            if (graph->FindRoute(&route, start, goal, 0)) {
                rows[from][to] = graph->GetEdge(route.edgeIds[0])->index;
            } else { rows[from][to] = -1; }
            if (progress)
                progress((count * from + to) * 100 / (count * count));
        }
    }
    graph->heuristic = savedHeuristic;
    graph->costPolicy = savedPolicy;
    return true;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FDF40);
#endif
#ifdef NON_MATCHING
// Unmatched: header-write join and conversion buffer lifetimes.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FE370);
#endif
#ifdef NON_MATCHING
// Unmatched: route append helper, vector temporary and traversal scheduling.
bool Kaim::CAstarData::ExtractRoute(unsigned int from, unsigned int to, RouteBuffers *route) {
    route->Clear();
    if (from == to) {
        SearchNode *p = graph->GetNode(to);
        route->points[0] = *(Vec3 *)&p->x;
        route->guards[0] = 0;
        route->nodeIds[0] = graph->GetNode(from)->id;
        route->count = 1;
        return true;
    }
    unsigned int i = 0;
    SearchNode *p = graph->GetNode(from);
    route->points[0] = *(Vec3 *)&p->x;
    route->guards[0] = 0;
    route->nodeIds[0] = graph->GetNode(from)->id;
    ++route->count;
    do {
        ++i;
        if (route->count == route->capacity) {
            while (from != to) {
                unsigned int e = rows[from][to];
                if (e == (unsigned int)-1)
                    return false;
                SearchEdge *edge = graph->GetEdge(e);
                from = edge->End()->id;
                route->length += edge->GeometricLength();
            }
            return true;
        }
        unsigned int e = rows[from][to];
        if (e == (unsigned int)-1)
            return false;
        SearchEdge *edge = graph->GetEdge(e);
        from = edge->End()->id;
        p = graph->GetNode(from);
        route->points[i] = *(Vec3 *)&p->x;
        route->nodeIds[i] = graph->GetNode(from)->id;
        route->guards[i] = 0;
        route->edgeIds[i-1] = e;
        ++route->count;
        route->guards[i-1] = edge->Guard();
    } while (from != to);
    return true;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FE570);
#endif
