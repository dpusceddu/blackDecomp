#include "include_asm.h"

#include "kynapse/graph/spatial_iteration.hpp"
#ifdef NON_MATCHING
#include "kynapse/graph/spatial.hpp"
#endif

namespace Kaim {

CSpatialGraph::CSpatialGraph():flags(31),coverageDistance(-1.0f),nodeCapacity(0),nodeSlots(0),nodeCount(0),nodes(0),nodeTable1c(0),firstEdgeFrom(0),firstEdgeTo(0),edgeCapacity(0),edgeSlots(0),edgeCount(0),edges(0),edgeEnd(0),edgeStart(0),edgeTable40(0),edgeNext(0),edgeTable48(0),edgeTable4c(0),edgeTable50(0),costPolicy(0),heuristic(0) {
 syntheticEdge.graph=this;
 syntheticEdge.index=-1;syntheticNodes[0].id=-1;syntheticNodes[1].id=-1;
 syntheticNodes[0].graph=this;syntheticNodes[1].graph=this;
 syntheticGeometricLength=0;syntheticLength=0;syntheticGuard=0;
}
CSpatialGraph::CSpatialGraph(const CSpatialGraph &rhs):flags(31),coverageDistance(-1.0f),nodeCapacity(0),nodeSlots(0),nodeCount(0),nodes(0),nodeTable1c(0),firstEdgeFrom(0),firstEdgeTo(0),edgeCapacity(0),edgeSlots(0),edgeCount(0),edges(0),edgeEnd(0),edgeStart(0),edgeTable40(0),edgeNext(0),edgeTable48(0),edgeTable4c(0),edgeTable50(0),costPolicy(0),heuristic(0) {
 syntheticEdge.graph=this;syntheticNodes[0].graph=this;syntheticNodes[1].graph=this;
 syntheticGeometricLength=0;syntheticLength=0;syntheticGuard=0;
 syntheticEdge.index=-1;syntheticNodes[0].id=-1;syntheticNodes[1].id=-1;
 *this=rhs;
}
bool CSpatialGraph::RemoveNode(unsigned int index){
 SpatialNode *node=GetNode(index);if(!node)return false;
 SpatialEdge *edge=IncidentEdge<true>(node,0);
 while(edge){RemoveEdge(edge->index);edge=IncidentEdge<true>(node,0);}
 edge=IncidentEdge<false>(node,0);
 while(edge){RemoveEdge(edge->index);edge=IncidentEdge<false>(node,0);}
 node->id=-1;--nodeCount;return true;
}
SpatialEdge *CSpatialGraph::FindEdge(const SpatialIndex&a,const SpatialIndex&b){return FindEdge(a.value,b.value);}
static inline int SamePoint(const Vec3 &a,const Vec3 &b){return a.x==b.x&&a.y==b.y&&a.z==b.z;}
unsigned int RouteBuffers::FindPoint(const Vec3 *point)const{for(unsigned int i=0;i<count;++i)if(SamePoint(points[i],*point))return i;return (unsigned int)-1;}
}


INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_spatial_2f5c10", func_002F5E20);
#ifdef NON_MATCHING
#define CONVERT(field) { for(unsigned int word=0;word<sizeof(field)/4;++word){unsigned int *p=(unsigned int*)&(field);p[word]=p[word];} }
#undef CONVERT
namespace Kaim {
// Unmatched: iterator and endpoint-accessor context.
SpatialEdge* CSpatialGraph::FindEdge(unsigned int endId, unsigned int startId)
{
    if (edgeCount == 0)
        return 0;
    if ((flags & 8) == 0) {
        unsigned int seen = 0;
        if (edgeCount != 0) {
            unsigned int slot = 0;
            do {
                if (slot < edgeCapacity && edges[slot].index != -1 && &edges[slot]) {
                    SpatialEdge* edge = &edges[slot];
                    CSpatialGraph* owner = edge->graph;
                    ++seen;
                    SpatialNode* end;
                    if (edge == &owner->syntheticEdge)
                        end = &owner->syntheticNodes[0];
                    else
                        end = &owner->nodes[owner->edgeEnd[edge->index]];
                    if ((unsigned int)end->id == endId) {
                        SpatialNode* start;
                        if (edge == &owner->syntheticEdge)
                            start = &owner->syntheticNodes[1];
                        else
                            start = &owner->nodes[owner->edgeStart[edge->index]];
                        if ((unsigned int)start->id == startId)
                            return edge;
                    }
                }
                ++slot;
            } while (seen < edgeCount);
        }
        return 0;
    }
    unsigned int index = firstEdgeTo[endId];
    if (index != (unsigned int)-1) {
        while ((unsigned int)edgeStart[index] != startId) {
            index = edgeNext[index];
            if (index == (unsigned int)-1)
                return 0;
        }
        if (index < edgeCapacity)
            return GetEdge(index);
    }
    return 0;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_spatial_2f5c10", func_002F66D0);
#endif
#ifdef NON_MATCHING
#define CONVERT(field) { for(unsigned int word=0;word<sizeof(field)/4;++word){unsigned int *p=(unsigned int*)&(field);p[word]=p[word];} }
namespace Kaim {
// Unmatched: not compared to the original beyond its call and data references.
bool CSpatialGraph::LoadOld(FileService* files, const void* resource)
{
    float nodeBuffer[0x320 * 5];
    unsigned int edgeBuffer[0x800 * 2];
    if (files->Read(resource, &coverageDistance, 4) != 4) {
        files->Close(resource);
        return false;
    }
    CONVERT(coverageDistance);
    if (files->Read(resource, &nodeCount, 4) != 4) {
        files->Close(resource);
        return false;
    }
    CONVERT(nodeCount);
    if (nodeCount == 0) {
        files->Close(resource);
        return true;
    }
    nodeCapacity = 0;
    nodeSlots = nodeCount;
    unsigned int slots = nodeCount;
    nodes = new SpatialNode[slots];
    unsigned int remaining = nodeCount;
    while (remaining != 0) {
        unsigned int chunk = remaining > 0x320 ? 0x320 : remaining;
        if (files->Read(resource, nodeBuffer, chunk * sizeof(SpatialNode)) != (int)(chunk * sizeof(SpatialNode))) {
            files->Close(resource);
            return false;
        }
        remaining -= chunk;
        for (unsigned int i = 0; i < chunk; ++i) {
            nodes[nodeCapacity].id = nodeCapacity;
            nodes[nodeCapacity].graph = (CSpatialGraph*)this;
            nodes[nodeCapacity].x = nodeBuffer[i * 5];
            nodes[nodeCapacity].y = nodeBuffer[i * 5 + 1];
            nodes[nodeCapacity].z = nodeBuffer[i * 5 + 2];
            ++nodeCapacity;
        }
    }
    if (files->Read(resource, &edgeCount, 4) != 4) {
        files->Close(resource);
        return false;
    }
    CONVERT(edgeCount);
    if (edgeCount == 0) {
        files->Close(resource);
        return true;
    }
    edgeCapacity = 0;
    edgeSlots = edgeCount;
    unsigned int edgeTotal = edgeCount;
    edges = new SpatialEdge[edgeTotal];
    edgeEnd = (int*)Allocate(edgeTotal << 2);
    edgeStart = (int*)Allocate(edgeTotal << 2);
    remaining = edgeCount;
    while (remaining != 0) {
        unsigned int chunk = remaining > 0x800 ? 0x800 : remaining;
        if (files->Read(resource, edgeBuffer, chunk * 8) != (int)(chunk * 8)) {
            files->Close(resource);
            return false;
        }
        for (unsigned int i = 0; i < chunk * 2; ++i)
            CONVERT(edgeBuffer[i]);
        remaining -= chunk;
        for (unsigned int i = 0; i < chunk; ++i) {
            edges[edgeCapacity].index = edgeCapacity;
            edges[edgeCapacity].graph = (CSpatialGraph*)this;
            edgeEnd[edgeCapacity] = edgeBuffer[i * 2];
            edgeStart[edgeCapacity] = edgeBuffer[i * 2 + 1];
            ++edgeCapacity;
        }
    }
    SetFlags(flags);
    files->Close(resource);
    return true;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_spatial_2f5c10", func_002F6880);
#endif
#ifdef NON_MATCHING
#define CONVERT(field) { for(unsigned int word=0;word<sizeof(field)/4;++word){unsigned int *p=(unsigned int*)&(field);p[word]=p[word];} }
namespace Kaim {
// Unmatched: field conversion helpers and error cleanup block ordering.
bool CSpatialGraph::Load(const void* resource)
{
    Reset();
    FileService* files = D_003C9ED4->files;
    if (!files->Exists(resource))
        return false;
    char header[0x40];
    unsigned int version;
    int headerRead = files->Read(resource, header, strlen(D_00407C28));
    int versionRead = files->Read(resource, &version, 4);
    if (headerRead != strlen(D_00407C28) || versionRead != 4) {
        files->Close(resource);
        return false;
    }
    header[headerRead] = 0;
    if (_stricmp(header, D_00407C28) != 0) {
        files->Close(resource);
        return false;
    }
    if (version == 1) {
        if (!LoadOld(files, resource))
            return false;
        files->Close(resource);
        return true;
    }
    if (version != 2) {
        files->Close(resource);
        return false;
    }
    if(files->Read(resource,&flags,4)!=4){files->Close(resource);return false;}CONVERT(flags);
if(files->Read(resource,&coverageDistance,4)!=4){files->Close(resource);return false;}CONVERT(coverageDistance);
if(files->Read(resource,&nodeCapacity,4)!=4){files->Close(resource);return false;}CONVERT(nodeCapacity);
if(files->Read(resource,&nodeSlots,4)!=4){files->Close(resource);return false;}CONVERT(nodeSlots);
if(files->Read(resource,&nodeCount,4)!=4){files->Close(resource);return false;}CONVERT(nodeCount);
    unsigned int slots = nodeSlots;
    nodes = new SpatialNode[slots];
    for (unsigned int i = 0; i < nodeCount; ++i) {
        SpatialNode* node = &nodes[i];
        int junk;
        if(files->Read(resource,&node->id,4)!=4){files->Close(resource);return false;}CONVERT(node->id);
        if(files->Read(resource,&node->x,4)!=4){files->Close(resource);return false;}CONVERT(node->x);
        if(files->Read(resource,&node->y,4)!=4){files->Close(resource);return false;}CONVERT(node->y);
        if(files->Read(resource,&node->z,4)!=4){files->Close(resource);return false;}CONVERT(node->z);
        if(files->Read(resource,&junk,4)!=4){files->Close(resource);return false;}
        node->graph = (CSpatialGraph*)this;
    }
    if (flags & 1) {
        unsigned int bytes = nodeSlots << 2;
        nodeTable1c = (int*)Allocate(bytes);
        if (files->Read(resource, nodeTable1c, bytes) != (int)bytes) {
            files->Close(resource);
            return false;
        }
        for (unsigned int i = 0; i < nodeSlots; ++i)
            CONVERT(nodeTable1c[i]);
        for (unsigned int i = 0; i < nodeCount; ++i)
            nodeTable1c[i] = 0;
    }
    if (flags & 0x10) {
        unsigned int bytes = nodeSlots << 2;
        firstEdgeFrom = (int*)Allocate(bytes);
        if (files->Read(resource, firstEdgeFrom, bytes) != (int)bytes) {
            files->Close(resource);
            return false;
        }
        for (unsigned int i = 0; i < nodeSlots; ++i)
            CONVERT(firstEdgeFrom[i]);
    }
    if (flags & 8) {
        unsigned int bytes = nodeSlots << 2;
        firstEdgeTo = (int*)Allocate(bytes);
        if (files->Read(resource, firstEdgeTo, bytes) != (int)bytes) {
            files->Close(resource);
            return false;
        }
        for (unsigned int i = 0; i < nodeSlots; ++i)
            CONVERT(firstEdgeTo[i]);
    }
    if(files->Read(resource,&edgeCapacity,4)!=4){files->Close(resource);return false;}CONVERT(edgeCapacity);
    if(files->Read(resource,&edgeSlots,4)!=4){files->Close(resource);return false;}CONVERT(edgeSlots);
    if(files->Read(resource,&edgeCount,4)!=4){files->Close(resource);return false;}CONVERT(edgeCount);

    unsigned int edgeBlockSlots = edgeSlots;
    edges = new SpatialEdge[edgeBlockSlots];
    for (unsigned int i = 0; i < edgeSlots; ++i) {
        SpatialEdge* edge = &edges[i];
        int junk;
        if(files->Read(resource,&edge->index,4)!=4){files->Close(resource);return false;}CONVERT(edge->index);
        if(files->Read(resource,&junk,4)!=4){files->Close(resource);return false;}
        edge->graph = (CSpatialGraph*)this;
    }
    // The per-edge tables hold edgeCount values each.
#define READ_EDGE_TABLE(table) \
    table = (int*)Allocate(edgeSlots << 2); \
    if (files->Read(resource, table, edgeCount << 2) != (int)(edgeCount << 2)) { \
        files->Close(resource); \
        return false; \
    } \
    for (unsigned int i = 0; i < edgeCount; ++i) \
        CONVERT(table[i]);
    READ_EDGE_TABLE(edgeEnd)
    READ_EDGE_TABLE(edgeStart)
    if (flags & 0x10) {
        READ_EDGE_TABLE(edgeTable40)
    }
    if (flags & 8) {
        READ_EDGE_TABLE(edgeNext)
    }
    if (flags & 4) {
        READ_EDGE_TABLE(edgeTable48)
    }
    if (flags & 1) {
        READ_EDGE_TABLE(edgeTable4c)
    }
    if (flags & 2) {
        READ_EDGE_TABLE(edgeTable50)
        for (unsigned int i = 0; i < edgeCount; ++i)
            edgeTable50[i] = 0;
    }
    files->Close(resource);
    return true;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/graph_spatial_2f5c10", func_002F6E08);
#endif
