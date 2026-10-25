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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FA4C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FA930);
