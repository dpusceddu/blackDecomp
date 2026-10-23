#include "campaign/graph/tables.hpp"
extern const char D_00407950[],D_00407F08[];
extern const int D_00407968,D_00407F1C;
int Kaim::CPathCostData::Save(const void *path) {
 if (table && size > 0) {
  void *file = D_00451228.open(path,"wb");
  if (!file) return 0;
  {
   float savedScale=scale; int version=D_00407968;
   if(D_00451228.write(D_00407950,1,func_0035CCD8(D_00407950),file)==func_0035CCD8(D_00407950)) {
    int wrote=D_00451228.write(&version,4,1,file);
    if(wrote==1 && D_00451228.write(&savedScale,4,1,file)==wrote) {
     if(D_00451228.write(table,1,size*size,file)==size*size) { D_00451228.close(file); return 1; }
     D_00451228.close(file);
    }
   }
   return 0;
  }
 }
 return 0;
}

#if 0

// Unmatched: saved-register allocation.
extern const char D_00407950[],D_00407F08[];
extern const int D_00407968,D_00407F1C;
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

// Unmatched: route temporaries, progress callback widths and loop register allocation.
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
    if (size < 1) {
        table = 0;
    } else {
        table = (unsigned char*)Allocate(size * size);
        lengths = (float*)Allocate(size * size * 4);
    }
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
            if (!graph->FindRoute(&route, start, goal, 0)) {
                total = -1.0f;
                ++failures;
            } else {
                total = 0;
                for (unsigned int i = 1; i < route.count; ++i) {
                    unsigned int edgeId = route.edgeIds[i - 1];
                    SearchEdge* edge = 0;
                    if (edgeId < graph->edgeCapacity) {
                        SearchEdge* candidate = &graph->edges[edgeId];
                        edge = candidate->index == -1 ? 0 : candidate;
                    }
                    SearchGraph* owner = edge->graph;
                    float length;
                    if (edge == &owner->syntheticEdge)
                        length = owner->syntheticLength;
                    else if (owner->edgeLengths == 0)
                        length = 0;
                    else
                        length = owner->edgeLengths[edge->index];
                    total = length + total;
                }
                edgesTotal += route.count;
            }
            lengths[cell] = total;
            ++routes;
            if (longest < total)
                longest = total;
            if (progress) {
                float mean = 0;
                if (routes != failures)
                    mean = (float)(unsigned int)edgesTotal / (float)(unsigned int)(routes - failures);
                progress((size * from + to) * 100 / (size * size), routes, mean, failures);
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
        if (lengths[i] < 0)
            table[i] = 0xff;
        else
            table[i] = (unsigned char)(lengths[i] * scale);
    }
    if (lengths)
        D_003C87E0(lengths);
    graph->heuristic = savedHeuristic;
    graph->costPolicy = savedPolicy;
    return true;
}

#endif
