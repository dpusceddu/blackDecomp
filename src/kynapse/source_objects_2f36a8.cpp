#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/source_objects.hpp"

namespace Kaim {
// /SLUS_213.76 0x2f36a8

SquareTable::SquareTable(Description* newSource)
    : ObjectWithSource(newSource), unknown10(0), unknown14(0)
{
    size = newSource->size;
    if (size)
        cells = (unsigned char*)KaimAllocate(size * size);
    else
        cells = 0;
}

}  // namespace Kaim

#ifdef NON_MATCHING
#include "kynapse/graph/tables.hpp"
extern const char D_00407950[];
namespace Kaim {
// PS2 callback offset 0x68; this extension has no exact consumer yet.
struct TableStreamHooks : Hooks {
    unsigned int (*read)(void *, unsigned int, unsigned int, void *);
};
extern TableStreamHooks TableStreams __asm__("D_00451228");
inline float SearchEdge::AuthoredCost() const {
    if (this == &graph->syntheticEdge)
        return graph->syntheticLength;
    if (!graph->edgeLengths)
        return 0;
    return graph->edgeLengths[index];
}
}
// Unmatched: saved-register allocation for owner, configuration and header constant.
int Kaim::CPathCostData::Init(ChildBuffers *config) {
 ChildBuffers *raw=func_002E31E0(config,"RawData");
 if(!raw)return 0;
 FileService *files=D_003C9ED4->files;
 if(!files)return 0;
 if(!files->Exists(raw))return 0;
 char header[0x40]; int version;
 unsigned int length=files->Read(raw,header,func_0035CCD8(D_00407950));
 if(length!=func_0035CCD8(D_00407950))goto fail;
 if(files->Read(raw,&version,4)!=4)goto fail;
 header[length]=0;
 if(func_00360838(D_00407950,header) || version!=1)goto fail;
 if(files->Read(raw,&scale,4)!=4)goto fail;
 if(files->Read(raw,table,size*size)!=size*size)goto fail;
 files->Close(raw);return 1;
fail: files->Close(config);return 0;
}
// Unmatched: raw stream return joins and hook-base lifetime.
int Kaim::CPathCostData::LoadFile(const void *path) {
    void *file=Kaim::TableStreams.open(path,"rb");
    if(file){
        char header[64];int version;
        unsigned int n=Kaim::TableStreams.read(header,1,func_0035CCD8(D_00407950),file);
        if(n==func_0035CCD8(D_00407950) && Kaim::TableStreams.read(&version,4,1,file)==1){
            header[n]=0;
            if(!func_00360838(D_00407950,header) && version==1){
                if(Kaim::TableStreams.read(&scale,4,1,file)==1 && Kaim::TableStreams.read(table,1,size*size,file)==size*size){Kaim::TableStreams.close(file);return 1;}
                Kaim::TableStreams.close(file);return 0;
            }
        }
    }
    return 0;
}
// Unmatched: route-loop temporary lifetimes, sentinel materialization and callback scheduling.
int Kaim::CPathCostData::Build()
{
    float* lengths = 0;
    float longest = 0;
    RouteBuffers route;
    route.Reserve(graph->liveNodes);
    DefaultHeuristic heuristic;
    DefaultCostPolicy policy;
    void* savedPolicy; void* savedHeuristic = graph->heuristic;
    if (!savedHeuristic)
        graph->heuristic = &heuristic;
    savedPolicy = graph->costPolicy;
    if (!savedPolicy)
        graph->costPolicy = &policy;
    if (table)
        D_003C87E0(table);
    size = graph->liveNodes;
    if (size > 0) {
        table = (unsigned char*)Allocate(size * size);
        lengths = (float*)Allocate(size * size * 4);
    } else table=0;
    int routes = 0;
    int failures = 0;
    int edgesTotal = 0;
    for (int from = 0; from < size; ++from) {
        for (int to = 0; to < size; ++to) {
            int cell = size * from + to;
            if (from == to) {
                lengths[cell] = 0;
                continue;
            }
            SearchNode *start = graph->GetNode(from);
            SearchNode *goal = graph->GetNode(to);
            route.Clear();
            float total;
            if (graph->FindRoute(&route, start, goal, 0)) {
                total = 0;
                for (int i = 0; i+1 < (int)route.count; ++i) {
                    unsigned int edgeId = route.edgeIds[i];
                    float length=graph->GetEdge(edgeId)->AuthoredCost();
                    total = total + length;
                }
                edgesTotal += route.count;
            } else {total=-1.0f;++failures;}
            lengths[cell] = total;
            ++routes;
            if (longest < total)
                longest = total;
            if (progress) {
                int percentage=(from * size + to) * 100 / (size * size);
                float mean = 0;
                if (routes != failures)
                    mean = (float)(unsigned int)edgesTotal / (float)(unsigned int)(routes - failures);
                progress(percentage, routes, mean, failures);
            }
        }
    }
    if (progress) {
        float mean = 0;
        if (routes != failures)
            mean = (float)(unsigned int)edgesTotal / (float)(unsigned int)(routes - failures);
        progress(100, routes, mean, failures);
    }
    scale = 254.0f / longest;
    for (int i = 0; i < size * size; ++i) {
        if (lengths[i] >= 0)
            table[i] = (unsigned char)(scale * lengths[i]);
        else table[i] = 0xff;
    }
    if (lengths)
        D_003C87E0(lengths);
    graph->heuristic = savedHeuristic;
    graph->costPolicy = savedPolicy;
    return true;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F3770);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F3948);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F3AB0);
#endif
