#include "include_asm.h"

#include "kynapse/graph/spatial_iteration.hpp"

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

// Unplaced draft, not compiled: readable code kept for reference whose PS2 address is not established (docs/units.md, "Drafts").
#if 0
namespace Kaim {

// Unmatched: position-lvalue scheduling and array helper context; best23diff.
CSpatialGraph &CSpatialGraph::operator=(const CSpatialGraph &rhs){
 if(this!=&rhs){
 Reset();flags=rhs.flags;coverageDistance=rhs.coverageDistance;nodeCapacity=rhs.nodeCapacity;nodeSlots=rhs.nodeSlots;nodeCount=rhs.nodeCount;
 nodes=new SpatialNode[nodeSlots];
 for(unsigned int i=0;i<nodeSlots;++i){nodes[i].id=rhs.nodes[i].id;nodes[i].Position()=rhs.nodes[i].Position();nodes[i].graph=this;}
 if(HasFlag(1)){nodeTable1c=new int[nodeSlots];for(unsigned int i=0;i<nodeSlots;++i)nodeTable1c[i]=0;}
 if(HasFlag(16)){firstEdgeFrom=new int[nodeSlots];for(unsigned int i=0;i<nodeSlots;++i)firstEdgeFrom[i]=rhs.firstEdgeFrom[i];}
 if(HasFlag(8)){firstEdgeTo=new int[nodeSlots];for(unsigned int i=0;i<nodeSlots;++i)firstEdgeTo[i]=rhs.firstEdgeTo[i];}
 edgeCapacity=rhs.edgeCapacity;edgeSlots=rhs.edgeSlots;edgeCount=rhs.edgeCount;edges=new SpatialEdge[edgeSlots];
 edgeEnd=new int[edgeSlots];edgeStart=new int[edgeSlots];
 for(unsigned int i=0;i<edgeSlots;++i){edges[i].index=rhs.edges[i].index;edges[i].graph=this;edgeEnd[i]=rhs.edgeEnd[i];edgeStart[i]=rhs.edgeStart[i];}
 if(HasFlag(16)){edgeTable40=new int[edgeSlots];for(unsigned int i=0;i<edgeSlots;++i)edgeTable40[i]=rhs.edgeTable40[i];}
 if(HasFlag(8)){edgeNext=new int[edgeSlots];for(unsigned int i=0;i<edgeSlots;++i)edgeNext[i]=rhs.edgeNext[i];}
 if(HasFlag(4)){edgeTable48=new int[edgeSlots];for(unsigned int i=0;i<edgeSlots;++i)((float*)edgeTable48)[i]=((float*)rhs.edgeTable48)[i];}
 if(HasFlag(1)){edgeTable4c=new int[edgeSlots];for(unsigned int i=0;i<edgeSlots;++i)((float*)edgeTable4c)[i]=((float*)rhs.edgeTable4c)[i];}
 if(HasFlag(2)){edgeTable50=new int[edgeSlots];for(unsigned int i=0;i<edgeCount;++i)edgeTable50[i]=0;}
 }
 return *this;
}

// Unmatched: iterator source form and register allocation; best85diff.
SpatialEdge *CSpatialGraph::FindEdge(unsigned int endId,unsigned int startId){
 if(!edgeCount)return 0;
 if(!HasFlag(8)){
 unsigned int count=edgeCount,seen=0,slot=0;
 while(seen<count){SpatialEdge *edge=GetEdge(slot);if(edge){++seen;if(edge->EndNode()->id.value==endId&&edge->StartNode()->id.value==startId)return edge;}++slot;}
 return 0;
 }
 unsigned int index=firstEdgeTo[endId];
 while(index!=(unsigned int)-1){if((unsigned int)edgeStart[index]==startId)return GetEdge(index);index=edgeNext[index];}
 return 0;
}

// Unmatched: nested position/unsigned arrays give5diff, one epilogue restore.
SpatialNode *CSpatialGraph::AddNode(const Vec3 *point){
 if(nodeCapacity==nodeSlots){
  nodeSlots=nodeCapacity?nodeCapacity*2:8;
  SpatialNode *newNodes=new SpatialNode[nodeSlots];
  unsigned int *newTags=0;if(HasFlag(1))newTags=new unsigned int[nodeSlots];
  unsigned int *newIncoming=0;if(HasFlag(8))newIncoming=new unsigned int[nodeSlots];
  unsigned int *newOutgoing=0;if(HasFlag(16))newOutgoing=new unsigned int[nodeSlots];
  unsigned int i;
  for(i=0;i<nodeCapacity&&nodes;++i){newNodes[i]=nodes[i];if(newTags)newTags[i]=nodeTable1c[i];if(newIncoming)newIncoming[i]=firstEdgeTo[i];if(newOutgoing)newOutgoing[i]=firstEdgeFrom[i];}
  for(i=nodeCapacity;i<nodeSlots;++i){newNodes[i].id=i;newNodes[i].graph=this;if(newTags)newTags[i]=0;if(newIncoming)newIncoming[i]=-1;if(newOutgoing)newOutgoing[i]=-1;}
  ReleaseSpatialArray(nodes);nodes=newNodes;
  if(HasFlag(1)){ReleaseSpatialWords(nodeTable1c);nodeTable1c=newTags;}
  if(HasFlag(8)){ReleaseSpatialWords(firstEdgeTo);firstEdgeTo=newIncoming;}
  if(HasFlag(16)){ReleaseSpatialWords(firstEdgeFrom);firstEdgeFrom=newOutgoing;}
 }
 SpatialNode *node=nodes+nodeCapacity;
 node->Position()=*(const SpatialPosition*)point;
 if(HasFlag(16))firstEdgeFrom[nodeCapacity]=-1;
 if(HasFlag(8))firstEdgeTo[nodeCapacity]=-1;
 if(HasFlag(1))nodeTable1c[nodeCapacity]=0;
 ++nodeCount;++nodeCapacity;return node;
}

// Unmatched: array growth, float vector helpers and allocation context; best69diff.
SpatialEdge *CSpatialGraph::AddEdge(SpatialNode *end,SpatialNode *start){
 if(edgeCapacity==edgeSlots){
  edgeSlots=edgeCapacity?edgeCapacity*2:8;
  SpatialEdge *newEdges=new SpatialEdge[edgeSlots];
  int *newEnd=new int[edgeSlots];int *newStart=new int[edgeSlots];
  int *newLengths=0;if(HasFlag(4))newLengths=new int[edgeSlots];
  int *newTags=0;if(HasFlag(1))newTags=new int[edgeSlots];
  int *newGuards=0;if(HasFlag(2))newGuards=new int[edgeSlots];
  int *newOutgoing=0;if(HasFlag(16))newOutgoing=new int[edgeSlots];
  int *newIncoming=0;if(HasFlag(8))newIncoming=new int[edgeSlots];
  unsigned int i;
  for(i=0;i<edgeCapacity&&edges;++i){newEdges[i]=edges[i];newEnd[i]=edgeEnd[i];newStart[i]=edgeStart[i];if(newLengths)newLengths[i]=edgeTable48[i];if(newGuards)newGuards[i]=edgeTable50[i];if(newOutgoing)newOutgoing[i]=edgeTable40[i];if(newIncoming)newIncoming[i]=edgeNext[i];}
  for(i=edgeCapacity;i<edgeSlots;++i){newEdges[i].index=i;newEdges[i].graph=this;newEnd[i]=-1;newStart[i]=-1;if(newLengths)((float*)newLengths)[i]=3.402823466e38f;if(newGuards)newGuards[i]=0;if(newOutgoing)newOutgoing[i]=-1;if(newIncoming)newIncoming[i]=-1;}
  ReleaseSpatialArray(edges);edges=newEdges;
  ReleaseSpatialWords(edgeEnd);edgeEnd=newEnd;ReleaseSpatialWords(edgeStart);edgeStart=newStart;
  if(HasFlag(4)){ReleaseSpatialWords(edgeTable48);edgeTable48=newLengths;}
  if(HasFlag(1)){ReleaseSpatialWords(edgeTable4c);edgeTable4c=newTags;}
  if(HasFlag(2)){ReleaseSpatialWords(edgeTable50);edgeTable50=newGuards;}
  if(newOutgoing){ReleaseSpatialWords(edgeTable40);edgeTable40=newOutgoing;}
  if(newIncoming){ReleaseSpatialWords(edgeNext);edgeNext=newIncoming;}
 }
 edgeEnd[edgeCapacity]=end->id;edgeStart[edgeCapacity]=start->id;
 if(edgeTable48){((float*)edgeTable48)[edgeCapacity]=((SpatialVector*)&start->x)->DistanceTo(*(SpatialVector*)&end->x);}
 if(edgeTable50)edgeTable50[edgeCapacity]=0;
 if(HasFlag(8)){edgeNext[edgeCapacity]=firstEdgeTo[end->id];firstEdgeTo[end->id]=edgeCapacity;}
 if(HasFlag(16)){edgeTable40[edgeCapacity]=firstEdgeFrom[start->id];firstEdgeFrom[start->id]=edgeCapacity;}
 unsigned int index=edgeCapacity++;++edgeCount;return edges+index;
}

// Unmatched: cached chain-index lvalues and traversal helpers; best64diff.
bool CSpatialGraph::RemoveEdge(unsigned int index){
 SpatialEdge *edge=GetEdge(index);if(!edge)return false;
 if(edgeNext){SpatialNode *node=edge->EndNode();SpatialEdge *previous=0,*current=IncidentEdge<true>(node,0);
  while(current!=edge){unsigned int next=edgeNext[current->index];if(next==(unsigned int)-1)break;previous=current;current=edges+next;}
  if(previous)edgeNext[previous->index]=edgeNext[edge->index];else firstEdgeTo[node->id]=edgeNext[edge->index];
 }
 if(edgeTable40){SpatialNode *node=edge->StartNode();SpatialEdge *previous=0,*current=IncidentEdge<false>(node,0);
  while(current!=edge){unsigned int next=edgeTable40[current->index];if(next==(unsigned int)-1)break;previous=current;current=edges+next;}
  if(previous)edgeTable40[previous->index]=edgeTable40[edge->index];else firstEdgeFrom[node->id]=edgeTable40[edge->index];
 }
 --edgeCount;edge->index=-1;return true;
}

// Unmatched: typed node/edge assignment, source helpers and register allocation; best199diff.
void CSpatialGraph::Compact()
{
    unsigned int node = 0;
    unsigned int* nodeMap = new unsigned int[nodeCapacity];
    unsigned int* edgeMap = new unsigned int[edgeCapacity];
    for (unsigned int i = 0; i < nodeCapacity; ++i)
        nodeMap[i] = -1;
    for (unsigned int i = 0; i < edgeCapacity; ++i)
        edgeMap[i] = -1;
    int liveNodes = 0;
    for (node = 0; node < nodeCapacity; ++node) {
        if (SpatialNode *entry=GetNode(node)) {
            nodes[liveNodes] = *entry;
            nodes[liveNodes].id = liveNodes;
            nodeMap[node] = liveNodes;
            ++liveNodes;
        }
    }
    int liveEdges = 0;
    for (unsigned int edge = 0; edge < edgeCapacity; ++edge) {
        if (SpatialEdge *entry=GetEdge(edge)) {
            edges[liveEdges] = *entry;
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

// Unmatched: unsigned link arrays and inline getter lifetimes; best68diff.
void CSpatialGraph::SetFlags(unsigned int newFlags)
{
    flags = newFlags;
    if (HasFlag(1)) {
        if (!nodeTable1c)
            nodeTable1c = (unsigned int*)Allocate(nodeSlots << 2);
        if (!edgeTable4c)
            edgeTable4c = (unsigned int*)Allocate(edgeSlots << 2);
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
            edgeTable50 = (unsigned int*)Allocate(edgeSlots << 2);
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
            edgeTable48 = (unsigned int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < edgeSlots; ++i) {
                if (SpatialEdge *edge=GetEdge(i)) {
                    SpatialNode* end = edge->EndNode();
                    SpatialNode* start = edge->StartNode();
                    ((float*)edgeTable48)[i]=((SpatialVector*)&start->x)->DistanceTo(*(SpatialVector*)&end->x);
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
            firstEdgeTo = (unsigned int*)Allocate(nodeSlots << 2);
            edgeNext = (unsigned int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < nodeSlots; ++i)
                firstEdgeTo[i] = -1;
            for (unsigned int i = 0; i < edgeSlots; ++i)
                edgeNext[i] = -1;
            for (unsigned int k = 0; k < edgeSlots; ++k) {
                unsigned int index = edgeSlots - k - 1;
                if (SpatialEdge *edge=GetEdge(index)) {
                    SpatialNode* end = edge->EndNode();
                    unsigned int* head = &firstEdgeTo[end->id];
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
            firstEdgeFrom = (unsigned int*)Allocate(nodeSlots << 2);
            edgeTable40 = (unsigned int*)Allocate(edgeSlots << 2);
            for (unsigned int i = 0; i < nodeSlots; ++i)
                firstEdgeFrom[i] = -1;
            for (unsigned int i = 0; i < edgeSlots; ++i)
                edgeTable40[i] = -1;
            for (unsigned int k = 0; k < edgeSlots; ++k) {
                unsigned int index = edgeSlots - k - 1;
                if (SpatialEdge *edge=GetEdge(index)) {
                    SpatialNode* start = edge->StartNode();
                    unsigned int* head = &firstEdgeFrom[start->id];
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
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F5E20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F66D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F6880);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F6E08);
