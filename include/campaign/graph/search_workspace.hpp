#ifndef BLACK_CAMPAIGN_GRAPH_SEARCH_WORKSPACE_HPP
#define BLACK_CAMPAIGN_GRAPH_SEARCH_WORKSPACE_HPP
#include "kynapse/compat.hpp"
#include "kynapse/point_mapper.hpp"

// Scoped PS2 A* views: list/cursor prefixes, array cookies and graph fields are
// checked against this TU. Unused slots and complete class identities remain provisional.
namespace KaimSearch {
extern const char AstarLoopName[] __asm__("D_004070D0");
inline float fabsf(float v){return __builtin_fabsf(v);}
struct Object {
    Object() {}
    virtual ~Object() {}
    static void *operator new(unsigned int size) { return Allocate(size); }
    static void operator delete(void *p) { D_003C87E0(p); }
};
struct GraphNode;
struct SearchCell : Object {
    GraphNode *value;
    SearchCell *previous,*next;
    unsigned char active;
    SearchCell():previous(0),next(0),active(0) {}
    static void *operator new[](unsigned int size) { return Allocate(size); }
    static void operator delete[](void *p) { D_003C87E0(p); }
};
struct NodeCursor : Object {
    SearchCell *node;
    NodeCursor(SearchCell *p=0):node(p) {}
    NodeCursor(const NodeCursor &other):Object(),node(other.node) {}
    NodeCursor &operator=(const NodeCursor &other){node=other.node;return *this;}
    virtual ~NodeCursor() {}
    NodeCursor &operator++(){node=node->next;return *this;}
    bool IsValid()const{return node!=0;}
    GraphNode *Get()const{return node->value;}
    static void *operator new[](unsigned int size) { return Allocate(size); }
    static void operator delete[](void *p) { D_003C87E0(p); }
};
struct SearchList : Object {
    SearchCell *storage,*head,*tail,*freeHead;
    unsigned int activeCount,capacity;
    SearchList(unsigned int n) {
        head=0;activeCount=0;capacity=n;freeHead=0;storage=0;tail=0;
        if(n) {
            storage=new SearchCell[n];freeHead=storage;storage[0].previous=0;
            for(unsigned int i=1;i<capacity;++i) {
                storage[i].previous=&storage[i-1];
                storage[i].previous->next=&storage[i];
            }
            storage[capacity-1].next=0;
        }
    }
    virtual ~SearchList() { if(capacity && storage) delete[] storage; }
    NodeCursor Begin(){return NodeCursor(head);}
    void Clear() {
        while(head) {head->active=0;SearchCell *next=head->next;head->next=freeHead;freeHead=head;head=next;}
        tail=0;activeCount=0;
    }
    void Remove(const NodeCursor &at) {
        SearchCell *node=at.node;node->active=0;
        if(node==head)head=node->next;
        if(node==tail)tail=node->previous;
        if(node->previous)node->previous->next=node->next;
        if(node->next)node->next->previous=node->previous;
        node->next=freeHead;freeHead=node;--activeCount;
    }
    NodeCursor Insert(GraphNode *const &value,NodeCursor before) {
        SearchCell *entry=freeHead;
        if(!entry)return NodeCursor(0);
        ++activeCount;freeHead=entry->next;entry->value=value;entry->active=1;
        if(!before.node) {
            if(!tail){head=entry;tail=entry;entry->next=0;head->previous=0;tail->previous=0;tail->next=0;return NodeCursor(entry);}
            entry->previous=tail;entry->next=0;tail->next=entry;tail=entry;return NodeCursor(entry);
        }
        SearchCell *previous=before.node->previous;entry->next=before.node;before.node->previous=entry;entry->previous=previous;
        if(previous)previous->next=entry;else head=entry;
        return NodeCursor(entry);
    }
};
struct SearchGraph;
struct SearchEdge;
struct EdgeGuard;
struct GraphNode {
    unsigned int id;
    float x,y,z;
    SearchGraph *graph;
    SearchEdge *GetOutgoing(unsigned int);
    SearchEdge *GetIncoming(unsigned int);
};
struct SearchEdge {
    int index;
    SearchGraph *graph;
    GraphNode *EndNode();
    EdgeGuard *Guard()const;
    GraphNode *StartNode();
    GraphNode *RawEnd() const __asm__("func_0038F2B0");
    GraphNode *RawStart() const __asm__("func_0038F2F0");
    float GetAuthoredLength() const;
};
struct CostPolicy;
struct EdgeGuard {
    virtual ~EdgeGuard();virtual void Slot1();virtual void Slot2();
    virtual void Slot3();virtual void Slot4();
    virtual bool Cost(void*,CostPolicy*,float*);
};
struct CostPolicy {
    virtual ~CostPolicy();virtual void Slot1();
    virtual bool Cost(SearchEdge*,void*,float*);
};
struct HeuristicPolicy {
    virtual ~HeuristicPolicy();
    virtual bool Estimate(void*,GraphNode*,GraphNode*,float*);
};
struct SearchRoute;
struct SearchGraph {
    void *vtable;
    unsigned int flags;
    float graphRadius;
    unsigned int nodeCapacity,unknown10;
    int liveNodes;
    GraphNode *nodes;
    SearchEdge **predecessors;
    int *incomingHeads,*outgoingHeads;
    unsigned int edgeCapacity,edgeSlots,edgeCount;
    SearchEdge *edges;
    unsigned int *edgeEnd,*edgeStart;
    int *incomingNext;
    unsigned int *outgoingNext;
    float *geometricLengths,*edgeCosts;
    EdgeGuard **edgeGuards;
    CostPolicy *costPolicy;
    HeuristicPolicy *heuristic;
    SearchEdge syntheticEdge;
    GraphNode syntheticEnd,syntheticStart;
    float syntheticGeometricLength,syntheticCost;
    EdgeGuard *syntheticGuard;
    unsigned int LiveEdges()const __asm__("func_00391620");
    void Expand(GraphNode*,GraphNode*,GraphNode*,void*);
    bool FindRoute(SearchRoute*,GraphNode*,GraphNode*,void*);
    bool ReconstructRoute(SearchRoute*,GraphNode*);
    unsigned int AdvanceTimed(SearchRoute*,GraphNode*,GraphNode*,void*,unsigned int*,float*,float*,float,float,unsigned int);
};
inline EdgeGuard *SearchEdge::Guard()const {
    if(this==&graph->syntheticEdge)return graph->syntheticGuard;
    if(!graph->edgeGuards)return 0;
    return graph->edgeGuards[index];
}
inline GraphNode *SearchEdge::EndNode() {
    SearchGraph *owner=graph;
    if(this==&owner->syntheticEdge)return &owner->syntheticEnd;
    return &owner->nodes[owner->edgeEnd[index]];
}
inline GraphNode *SearchEdge::StartNode() {
    SearchGraph *owner=graph;
    if(this==&owner->syntheticEdge)return &owner->syntheticStart;
    return &owner->nodes[owner->edgeStart[index]];
}
inline float SearchEdge::GetAuthoredLength()const {
    if(this==&graph->syntheticEdge)return graph->syntheticGeometricLength;
    if(!graph->geometricLengths) {
        GraphNode *a=RawEnd(),*b=RawStart();
        float dx=b->x-a->x,dy=b->y-a->y,dz=b->z-a->z;
        return sqrtf(dz*dz+dx*dx+dy*dy);
    }
    return graph->geometricLengths[index];
}
inline SearchEdge *GraphNode::GetOutgoing(unsigned int ordinal) {
    SearchGraph *owner=graph;
    if(!owner->outgoingHeads) {
        unsigned int seen=0,slot=0,found=0;
        while(seen<owner->LiveEdges()) {
            extern int EdgeId(const SearchEdge*) __asm__("func_00383D40");
            if(EdgeId(owner->edges+slot)!=-1) {++seen;if(owner->edgeEnd[slot]==id && found++==ordinal)return owner->edges+slot;}
            ++slot;
        }
    }else {
        unsigned int found=0;
        for(int edge=owner->outgoingHeads[id];edge!=-1;edge=owner->outgoingNext[edge])if(found++==ordinal)return owner->edges+edge;
    }
    return 0;
}
inline SearchEdge *GraphNode::GetIncoming(unsigned int ordinal) {
    SearchGraph *owner=graph;
    if(!owner->incomingHeads) {
        unsigned int seen=0,slot=0,found=0;
        while(seen<owner->LiveEdges()) {
            extern int EdgeId(const SearchEdge*) __asm__("func_00383D40");
            if(EdgeId(owner->edges+slot)!=-1) {++seen;if(owner->edgeStart[slot]==id && found++==ordinal)return owner->edges+slot;}
            ++slot;
        }
    }else {
        unsigned int found=0;
        for(int edge=owner->incomingHeads[id];edge!=-1;edge=owner->incomingNext[edge])if(found++==ordinal)return owner->edges+edge;
    }
    return 0;
}
struct SearchPosition {float x,y,z;SearchPosition &operator=(const SearchPosition&v){x=v.x;y=v.y;z=v.z;return *this;}};
struct SearchRoute {
    void *vtable;
    SearchGraph *graph;
    unsigned int count;
    unsigned int *nodeIds,*edgeIds;
    SearchPosition *positions;
    EdgeGuard **guards;
    unsigned int capacity;
    bool truncated;
    unsigned char unknown21[3];
    float length;
};
inline SearchEdge *PredecessorOf(GraphNode *node) {
    SearchEdge **table=node->graph->predecessors;
    if(!table)return 0;
    return table[node->id];
}
struct Traversal : Object {
    virtual ~Traversal() {}
    virtual void Slot1(GraphNode*) {}
    virtual void Begin(GraphNode*) {}
    virtual bool Slot3(GraphNode*) {return true;}
    virtual bool Relax(SearchEdge*) {return true;}
};
struct RelaxVisitor : Traversal {
    virtual ~RelaxVisitor() {}
    virtual void Begin(GraphNode*) __asm__("func_0038F2A8");
    virtual bool Relax(SearchEdge*) __asm__("func_0038F668");
    GraphNode *current,*goal,*start;
    SearchGraph *graph;
    void *context;
    bool EnumerateOutgoingEdges(GraphNode*);
};
extern unsigned int gSearchStart __asm__("D_003CA540");
extern int gSearchFlag __asm__("D_003CA53C");
extern int gSearchCapacity __asm__("D_003CA520");
extern SearchList *gOpenList __asm__("D_003CA524"),*gClosedList __asm__("D_003CA528");
extern NodeCursor *gOpenHandles __asm__("D_003CA52C"),*gClosedHandles __asm__("D_003CA530");
extern float *gCostSoFar __asm__("D_003CA534"),*gScore __asm__("D_003CA538");
extern int gRelaxCount __asm__("D_003CA548"),gProfileIndex __asm__("D_003CA544");
extern float gProfileTotal __asm__("D_00450260");
extern unsigned char gTimedActive __asm__("D_003CA54C");
extern GraphNode *gTimedStart __asm__("D_003CA53C"),*gSavedStart __asm__("D_003CA550"),*gSavedGoal __asm__("D_003CA554");
extern void *gSavedContext __asm__("D_003CA558"),*gSavedHeuristic __asm__("D_003CA55C"),*gSavedCost __asm__("D_003CA560");
extern float (*gSearchClock)() __asm__("D_00451230");
struct NameTableC {int FindName(const char*)const __asm__("func_002E94B8");};
NameTableC *GetNameTables() __asm__("func_002E91C0");
void FreeSearch();
bool InitSearch(unsigned int);
NodeCursor InsertByScore(SearchList*,GraphNode*);
#define SEARCH_OFFSET(type,field,n) typedef char type##field##Offset[(unsigned int)&((type*)0)->field==n?1:-1]
SEARCH_OFFSET(SearchGraph,syntheticEnd,0x64);
SEARCH_OFFSET(SearchGraph,syntheticStart,0x78);
SEARCH_OFFSET(SearchList,head,8);
SEARCH_OFFSET(NodeCursor,node,4);
#undef SEARCH_OFFSET
}
#endif
