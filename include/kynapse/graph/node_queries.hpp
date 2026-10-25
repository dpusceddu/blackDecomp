#ifndef BLACK_GRAPH_NODE_QUERIES_HPP
#define BLACK_GRAPH_NODE_QUERIES_HPP
// Scoped PS2 graph-query views. RTTI establishes the object/traversal hierarchy;
// unused callback signatures and unmatched algorithm source shapes remain provisional.
#include "kynapse/compat.hpp"

// Navigation graph traversal and the nearest-node visitors.
extern "C" int __cdecl _stricmp(const char*, const char*);

struct Vec3 {
    float x, y, z;
    Vec3 &operator=(const Vec3 &other){x=other.x;y=other.y;z=other.z;return *this;}
};

struct NavNode {
    unsigned int id;                                // 0x00 (-1 marks a free slot)
    Vec3 position;
    int unknown10;
    unsigned int CountOutgoing();
    unsigned int CountIncoming();
};

float Kaim_ManhattanDistance(const Vec3* a, const Vec3* b);
extern const double kZeroDouble;

struct NodeGraph {
    unsigned char unknown00[0xc];
    unsigned int capacity;
    unsigned char unknown10[4];
    unsigned int liveCount;
    NavNode* nodes;                        // 0x18 (0x14 bytes each)
};

extern void (*QueryRelease)(void*) __asm__("D_003C87E0");
struct QueryObject {virtual ~QueryObject(){} static void operator delete(void *p){QueryRelease(p);}};
struct NodeVisitor : QueryObject {
    NodeVisitor() {}
    virtual ~NodeVisitor() {}
    virtual void Begin(NodeGraph*) {}              // slot 1
    virtual void Slot2() {}
    virtual bool Consider(NavNode*) { return true; }   // slot 3
    virtual void Slot4() {}

    bool VisitNodes(NodeGraph* graph);
};



// PS2 nearest-vertex traversal vtable: 0x3eed38.
struct NearestSimpleVisitor : NodeVisitor {
    double best;
    NavNode* result;
    Vec3 point;
    unsigned char needOutgoing;
    unsigned char needIncoming;

    NearestSimpleVisitor() {}
    virtual ~NearestSimpleVisitor() {}
    virtual void Begin(NodeGraph* graph);
    virtual bool Consider(NavNode* node);
};






NavNode* Kaim_FindNearestNodeSimple(NodeGraph* graph, const Vec3* point, bool needOutgoing, bool needIncoming);


// PS2 locally-visible traversal vtable: 0x3eecc8.
struct AuthoredProperty {
    unsigned char unknown00[4];
    float value;
};
struct EntityObject { unsigned char unknown00[0xc]; float frameTime; };
extern EntityObject* gEngine;
extern const float kDefaultFloat;
extern int gAuthoredHeightKey;
struct Actor {
    AuthoredProperty* GetAuthoredProperty(const void* key);
};
bool Kaim_TestSegment(const float* from, const float* to, Actor* actor, int mode, float radius);

struct NearestNodeVisitor : NodeVisitor {
    double best;
    float radius;
    int unknown14;
    NavNode* result;
    Vec3 point;
    float height;
    Actor* actor;
    bool withinRadius;
    bool visible;
    float radiusSquared;
    unsigned char needOutgoing;
    unsigned char needIncoming;

    NearestNodeVisitor() {}
    virtual ~NearestNodeVisitor() {}
    virtual void Begin(NodeGraph* graph);
    virtual bool Consider(NavNode* node);
};



static inline double SquaredDistance(const Vec3* a, const Vec3* b)
{
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    double dz = a->z - b->z;
    return dz * dz + dy * dy + dx * dx;
}




NavNode* Kaim_FindNearestNode(NodeGraph* graph, const Vec3* point, Actor* actor, float radius, unsigned int needOutgoing,
                              unsigned int needIncoming);


#include "game/classes/other/FindNearestVertexTraversal.hpp"
#include "game/classes/other/FindNearestVisibleTraversal.hpp"
#include "game/classes/other/FindNearestLocallyVisibleTraversal.hpp"
#include "game/classes/other/FindNearestEdgeTraversal.hpp"

struct QueryGraph;
struct QueryEdge {
    unsigned int index;
    QueryGraph *graph;
    int Id() const __asm__("func_00383D40");
    NavNode *EndpointA() const;
    NavNode *EndpointB() const;
};
struct QueryGraph : NodeGraph {
    unsigned int unknown1c; // Fields below verified against the PS2 traversal code.
    int *incomingHead, *outgoingHead;
    unsigned int edgeCapacity, edgeSlots, edgeCount;
    QueryEdge *edges;
    unsigned int *endpointA, *endpointB;
    int *incomingNext, *outgoingNext;
    unsigned char unknown48[0x14];
    QueryEdge syntheticEdge;
    NavNode syntheticA, syntheticB;
    unsigned int LiveEdges() const __asm__("func_00391620");
    int HasOutgoingHeads() const __asm__("func_00391710");
    int HasIncomingHeads() const __asm__("func_00391720");
};
inline NavNode *QueryEdge::EndpointA() const {
    if (this == &graph->syntheticEdge) return &graph->syntheticA;
    return &graph->nodes[graph->endpointA[index]];
}
inline NavNode *QueryEdge::EndpointB() const {
    if (this == &graph->syntheticEdge) return &graph->syntheticB;
    return &graph->nodes[graph->endpointB[index]];
}
static inline bool QuerySameIndex(unsigned int lhs,unsigned int rhs){return lhs==rhs;}
inline NavNode *QueryNodeAt(NodeGraph *graph, unsigned int id) {
    if (id >= graph->capacity) return 0;
    NavNode *node = &graph->nodes[id];
    return node->id==(unsigned int)-1 ? 0 : node;
}
inline QueryEdge *QueryEdgeAt(QueryGraph *graph, unsigned int id) {
    if (id >= graph->edgeCapacity) return 0;
    QueryEdge *edge = &graph->edges[id];
    return edge->index==(unsigned int)-1 ? 0 : edge;
}
inline unsigned int NavNode::CountOutgoing() {
    QueryGraph *owner = (QueryGraph *)unknown10;
    unsigned int count = 0;
    if (owner->edgeCount) {
        if (!owner->HasOutgoingHeads()) {
            unsigned int seen = 0, index = 0;
            while (seen < owner->LiveEdges()) {
                if (owner->edges[index].Id() != -1) {
                    ++seen;
                    if (owner->endpointA[index] == (unsigned int)id) ++count;
                }
                ++index;
            }
        } else {
            for (int edge = owner->outgoingHead[id]; edge != -1; edge = owner->outgoingNext[edge]) ++count;
        }
    }
    return count;
}
inline unsigned int NavNode::CountIncoming() {
    QueryGraph *owner = (QueryGraph *)unknown10;
    unsigned int count = 0;
    if (!owner->HasIncomingHeads()) {
        unsigned int seen = 0, index = 0;
        while (seen < owner->LiveEdges()) {
            if (owner->edges[index].Id() != -1) {
                ++seen;
                if (owner->endpointB[index] == (unsigned int)id) ++count;
            }
            ++index;
        }
    } else {
        for (int edge = owner->incomingHead[id]; edge != -1; edge = owner->incomingNext[edge]) ++count;
    }
    return count;
}
inline bool NodeVisitor::VisitNodes(NodeGraph *graph) {
    Begin(graph);
    unsigned int slot = 0, visited = 0;
    if (graph->liveCount) {
        do {
            NavNode *node = QueryNodeAt(graph, slot);
            if (node) {
                ++visited;
                if (!Consider(node)) return false;
            }
            ++slot;
        } while (visited < graph->liveCount);
    }
    return true;
}
struct VisibleNodeVisitor : NodeVisitor {
    double best;
    unsigned int unknown10;
    NavNode *result;
    Vec3 point;
    float height;
    Actor *actor;
    unsigned char needOutgoing, needIncoming;
    VisibleNodeVisitor() {}
    virtual ~VisibleNodeVisitor() {}
    virtual void Begin(NodeGraph *) __asm__("func_00392550");
    virtual bool Consider(NavNode *) __asm__("func_00392298");
};
// Slot signatures unused here remain provisional; the edge callbacks occupy slots2 and4.
struct EdgeVisitorRoot : QueryObject {
    EdgeVisitorRoot() {}
    virtual ~EdgeVisitorRoot() {}
    virtual void BeginNodes(NodeGraph *);
    virtual void BeginEdges(NodeGraph *);
    virtual void ConsiderNode(NavNode *);
    virtual bool ConsiderEdge(QueryEdge *);
    bool VisitEdges(QueryGraph *);
};
struct NearestEdgeVisitor : EdgeVisitorRoot {
    double best;
    float radius;
    QueryEdge *result;
    Vec3 point;
    NearestEdgeVisitor() {}
    virtual ~NearestEdgeVisitor() {}
    virtual void BeginEdges(NodeGraph *) __asm__("func_00392D38");
    virtual bool ConsiderEdge(QueryEdge *) __asm__("func_00392B48");
};
struct QueryPointIndex {
    void *vtable;
    NodeGraph *graph;
    unsigned int QueryBox(const Vec3 *, int **) __asm__("func_002EFF00");
};
extern unsigned int QueryOrder[] __asm__("D_00452730");
extern float QueryDistances[] __asm__("D_004536D0");
extern const int QueryHeightKey __asm__("D_00450940");
extern "C" {
    int func_0035E690(void (*)());
    void func_002FCA20();
    void func_002FCA90();
    int func_002FCA38(const void *, const void *);
    int func_002E27F8(const Vec3 *, const Vec3 *, Actor *, int, float);
    float func_00389140(const Vec3 *);
}
struct QueryVector {
    float x,y,z;
    QueryVector() {}
    QueryVector(float a,float b,float c):x(a),y(b),z(c){}
    QueryVector(const QueryVector &v):x(v.x),y(v.y),z(v.z){}
    QueryVector operator-(const QueryVector &v)const {return QueryVector(x-v.x,y-v.y,z-v.z);}
    QueryVector operator+(const QueryVector &v)const {return QueryVector(x+v.x,y+v.y,z+v.z);}
    QueryVector operator*(float f)const {return QueryVector(f*x,f*y,f*z);}
    QueryVector &operator=(const QueryVector &v){x=v.x;y=v.y;z=v.z;return *this;}
};
struct QueryDebugHooks {
    unsigned char unknown00[0x4c];
    void (*line)(const QueryVector *,const QueryVector *,int,int,int);
    void (*point)(const QueryVector *,int,int,int);
};
extern QueryDebugHooks QueryDebug __asm__("D_00451228");
extern EntityObject *QueryEngine __asm__("D_003C9ED4");
struct QueryPath {
    void *vtable;
    unsigned int slots;int count;
    unsigned int *nodeIds,*edgeIds;
    QueryVector *points;
    void **guards;
};
#define QUERY_OFFSET(type,field,offset) typedef char type##field##Offset[(unsigned int)&((type*)0)->field==offset?1:-1]
QUERY_OFFSET(QueryGraph, incomingHead,0x20);
QUERY_OFFSET(QueryGraph, edges,0x34);
QUERY_OFFSET(QueryGraph, syntheticA,0x64);
QUERY_OFFSET(QueryGraph, syntheticB,0x78);
QUERY_OFFSET(VisibleNodeVisitor,result,0x14);
QUERY_OFFSET(VisibleNodeVisitor,point,0x18);
#undef QUERY_OFFSET

inline bool EdgeVisitorRoot::VisitEdges(QueryGraph *graph){BeginEdges(graph);unsigned int slot=0,visited=0;if(graph->edgeCount){do{QueryEdge *edge=QueryEdgeAt(graph,slot);if(edge){++visited;if(!ConsiderEdge(edge))return false;}++slot;}while(visited<graph->edgeCount);}return true;}

#endif
