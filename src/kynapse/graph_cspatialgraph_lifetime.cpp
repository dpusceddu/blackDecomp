#include "include_asm.h"

#include "kynapse/graph/spatial.hpp"

void Kaim::CSpatialGraph::Reset()
{
    // The two object arrays carry the observed 16-byte allocation cookie.
    if (nodes) {
        D_003C87E0((char*)nodes-16);
        nodes = 0;
    }
    if (nodeTable1c) {
        D_003C87E0(nodeTable1c);
        nodeTable1c = 0;
    }
    if (firstEdgeFrom) {
        D_003C87E0(firstEdgeFrom);
        firstEdgeFrom = 0;
    }
    if (firstEdgeTo) {
        D_003C87E0(firstEdgeTo);
        firstEdgeTo = 0;
    }
    if (edges) {
        D_003C87E0((char*)edges-16);
        edges = 0;
    }
    if (edgeEnd) {
        D_003C87E0(edgeEnd);
        edgeEnd = 0;
    }
    if (edgeStart) {
        D_003C87E0(edgeStart);
        edgeStart = 0;
    }
    if (edgeTable48) {
        D_003C87E0(edgeTable48);
        edgeTable48 = 0;
    }
    if (edgeTable4c) {
        D_003C87E0(edgeTable4c);
        edgeTable4c = 0;
    }
    if (edgeTable50) {
        D_003C87E0(edgeTable50);
        edgeTable50 = 0;
    }
    if (edgeTable40) {
        D_003C87E0(edgeTable40);
        edgeTable40 = 0;
    }
    if (edgeNext) {
        D_003C87E0(edgeNext);
        edgeNext = 0;
    }
    nodeCount = 0;
    nodeSlots = 0;
    nodeCapacity = 0;
    edgeSlots = 0;
    edgeCount = 0;
    edgeCapacity = 0;
}
Kaim::CSpatialGraph::~CSpatialGraph()
{
    Reset();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F8DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F97A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FA030);
#ifdef NON_MATCHING
#define CONVERT(field) { for(unsigned int word=0;word<sizeof(field)/4;++word){unsigned int *p=(unsigned int*)&(field);p[word]=p[word];} }
#undef CONVERT
namespace Kaim {
// Unmatched: aggregate copy and iterator register allocation.
void CSpatialGraph::Compact()
{
    unsigned int node = 0;
    int* nodeMap = new int[nodeCapacity];
    int* edgeMap = new int[edgeCapacity];
    for (unsigned int i = 0; i < nodeCapacity; ++i)
        nodeMap[i] = -1;
    for (unsigned int i = 0; i < edgeCapacity; ++i)
        edgeMap[i] = -1;
    int liveNodes = 0;
    for (node = 0; node < nodeCapacity; ++node) {
        if (nodes[node].id != -1) {
            nodes[liveNodes] = nodes[node];
            nodes[liveNodes].id = liveNodes;
            nodeMap[node] = liveNodes;
            ++liveNodes;
        }
    }
    int liveEdges = 0;
    for (unsigned int edge = 0; edge < edgeCapacity; ++edge) {
        if (edges[edge].index != -1) {
            edges[liveEdges] = edges[edge];
            edges[liveEdges].index = liveEdges;
            edgeMap[edge] = liveEdges;
            ++liveEdges;
        }
    }
    for (node = 0; node < nodeCapacity; ++node) {
        if (nodeMap[node] != -1) {
            if (firstEdgeFrom) {
                int target = firstEdgeFrom[node];
                firstEdgeFrom[nodeMap[node]] = target == -1 ? -1 : edgeMap[target];
            }
            if (firstEdgeTo) {
                int target = firstEdgeTo[node];
                firstEdgeTo[nodeMap[node]] = target == -1 ? -1 : edgeMap[target];
            }
        }
    }
    for (unsigned int edge = 0; edge < edgeCapacity; ++edge) {
        if (edgeMap[edge] != -1) {
            if (edgeEnd)
                edgeEnd[edgeMap[edge]] = nodeMap[edgeEnd[edge]];
            if (edgeStart)
                edgeStart[edgeMap[edge]] = nodeMap[edgeStart[edge]];
            if (edgeTable40)
                edgeTable40[edgeMap[edge]] = edgeTable40[edge] == -1 ? -1 : edgeMap[edgeTable40[edge]];
            if (edgeNext)
                edgeNext[edgeMap[edge]] = edgeNext[edge] == -1 ? -1 : edgeMap[edgeNext[edge]];
            if (edgeTable48)
                edgeTable48[edgeMap[edge]] = edgeTable48[edge];
        }
    }
    nodeCount = liveNodes;
    nodeCapacity = liveNodes;
    edgeCount = liveEdges;
    edgeCapacity = liveEdges;
    D_003C87E0(nodeMap);
    D_003C87E0(edgeMap);
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FA4C8);
#endif
#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: flag predicates, edge helpers and float-distance scheduling (197 differing instructions).
void CSpatialGraph::SetFlags(unsigned int newFlags)
{
    flags = newFlags;
    if (HasFlag(1)) {
        if (!nodeTable1c)
            nodeTable1c = (int*)Allocate(nodeSlots << 2);
        if (!edgeTable4c)
            edgeTable4c = (int*)Allocate(edgeSlots << 2);
    } else {
        if (nodeTable1c) {
            D_003C87E0(nodeTable1c);
            nodeTable1c = 0;
        }
        if (edgeTable4c) {
            D_003C87E0(edgeTable4c);
            edgeTable4c = 0;
        }
    }
    if (HasFlag(2)) {
        if (!edgeTable50) {
            edgeTable50 = (int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < edgeSlots; ++i)
                edgeTable50[i] = 0;
        }
    } else {
        if (edgeTable50) {
            D_003C87E0(edgeTable50);
            edgeTable50 = 0;
        }
    }
    if (HasFlag(4)) {
        if (!edgeTable48) {
            edgeTable48 = (int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < edgeSlots; ++i) {
                if (i < edgeCapacity && edges[i].index != -1 && &edges[i]) {
                    SpatialEdge* edge = &edges[i];
                    SpatialNode* end = edge->EndNode();
                    SpatialNode* start = edge->StartNode();
                    float dz = start->z - end->z;
                    float dx = start->x - end->x;
                    float dy = start->y - end->y;
                    ((float*)edgeTable48)[i] = sqrtf(dz * dz + dx * dx + dy * dy);
                }
            }
        }
    } else {
        if (edgeTable48) {
            D_003C87E0(edgeTable48);
            edgeTable48 = 0;
        }
    }
    if (HasFlag(8)) {
        if (!firstEdgeTo) {
            firstEdgeTo = (int*)Allocate(nodeSlots << 2);
            edgeNext = (int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < nodeSlots; ++i)
                firstEdgeTo[i] = -1;
            for (unsigned int i = 0; i < edgeSlots; ++i)
                edgeNext[i] = -1;
            for (unsigned int k = 0; k < edgeSlots; ++k) {
                unsigned int index = edgeSlots - k - 1;
                if (index < edgeCapacity && edges[index].index != -1 && &edges[index]) {
                    SpatialEdge* edge = &edges[index];
                    SpatialNode* end = edge->EndNode();
                    int* head = &firstEdgeTo[end->id];
                    int previous = *head;
                    *head = edge->index;
                    edgeNext[edge->index] = previous;
                }
            }
        }
    } else {
        if (firstEdgeTo) {
            D_003C87E0(firstEdgeTo);
            firstEdgeTo = 0;
        }
        if (edgeNext) {
            D_003C87E0(edgeNext);
            edgeNext = 0;
        }
    }
    if (HasFlag(0x10)) {
        if (!firstEdgeFrom) {
            firstEdgeFrom = (int*)Allocate(nodeSlots << 2);
            edgeTable40 = (int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < nodeSlots; ++i)
                firstEdgeFrom[i] = -1;
            for (unsigned int i = 0; i < edgeSlots; ++i)
                edgeTable40[i] = -1;
            for (unsigned int k = 0; k < edgeSlots; ++k) {
                unsigned int index = edgeSlots - k - 1;
                if (index < edgeCapacity && edges[index].index != -1 && &edges[index]) {
                    SpatialEdge* edge = &edges[index];
                    SpatialNode* start = edge->StartNode();
                    int* head = &firstEdgeFrom[start->id];
                    int previous = *head;
                    *head = edge->index;
                    edgeTable40[edge->index] = previous;
                }
            }
        }
    } else {
        if (firstEdgeFrom) {
            D_003C87E0(firstEdgeFrom);
            firstEdgeFrom = 0;
        }
        if (edgeTable40) {
            D_003C87E0(edgeTable40);
            edgeTable40 = 0;
        }
    }
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FA930);
#endif
