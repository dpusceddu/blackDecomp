#include "include_asm.h"

#include "kynapse/graph/node_queries.hpp"


inline void QueryDrawPoint(const QueryVector *point, int red, int green, int blue)
{
    if (QueryDebug.point) QueryDebug.point(point, red, green, blue);
}
inline void QueryDrawLine(const QueryVector *from, const QueryVector *to, int red, int green, int blue)
{
    if (QueryDebug.line) QueryDebug.line(from, to, red, green, blue);
}

inline void *operator new(unsigned int,void *storage){return storage;}
extern NearestSimpleVisitor QuerySimple __asm__("D_004526D0");
extern unsigned int QuerySimpleGuard __asm__("D_004526F8");
extern NearestEdgeVisitor QueryEdgeStorage __asm__("D_00452700");
extern unsigned int QueryEdgeGuard __asm__("D_00452728");

#ifdef NON_MATCHING
// Unmatched: visitor and iterator register allocation.
NavNode *FindNearestVertex(NodeGraph *graph,const Vec3 *point,unsigned char outgoing,unsigned char incoming) {
    if (!QuerySimpleGuard) {
        new (&QuerySimple) NearestSimpleVisitor;
        QuerySimpleGuard=1;
        func_0035E690(func_002FCA20);
    }
    QuerySimple.point=*point;
    QuerySimple.needOutgoing=outgoing;
    QuerySimple.needIncoming=incoming;
    QuerySimple.VisitNodes(graph);
    return QuerySimple.result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FB6D8);
#endif
#ifdef NON_MATCHING
// Unmatched: visitor lifetime and register allocation.
NavNode *FindNearestVisible(NodeGraph *graph,const Vec3 *point,Actor *actor,unsigned char outgoing,unsigned char incoming) {
    VisibleNodeVisitor visitor;
    visitor.point=*point;
    AuthoredProperty *property=actor->GetAuthoredProperty(&QueryHeightKey);
    visitor.height=property?property->value:0;
    visitor.actor=actor;
    visitor.needOutgoing=outgoing;
    visitor.needIncoming=incoming;
    visitor.VisitNodes(graph);
    return visitor.result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FB850);
#endif
#ifdef NON_MATCHING
// Unmatched: visitor lifetime and loop register allocation.
NavNode *FindNearestLocal(NodeGraph *graph,const Vec3 *point,Actor *actor,float radius,unsigned char outgoing,unsigned char incoming) {
    NearestNodeVisitor visitor;
    visitor.point=*point;
    float graphRadius=*(float*)((unsigned char*)graph+8);
    visitor.radiusSquared=graphRadius*graphRadius;
    visitor.withinRadius=true;
    visitor.visible=true;
    AuthoredProperty *property=actor->GetAuthoredProperty(&QueryHeightKey);
    visitor.height=property?property->value:0;
    visitor.actor=actor;
    visitor.radius=radius;
    visitor.needOutgoing=outgoing;
    visitor.needIncoming=incoming;
    visitor.VisitNodes(graph);
    if (!visitor.result) {
        visitor.visible=false;
        visitor.VisitNodes(graph);
    }
    return visitor.result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FB9D0);
#endif
#ifdef NON_MATCHING
// Unmatched: adjacency inline helpers and live-range allocation.
NavNode *QueryNearestCandidate(const Vec3 *point,Actor *actor,QueryPointIndex *index,unsigned char outgoing,unsigned char incoming) {
    int *candidates;
    unsigned int count=index->QueryBox(point,&candidates);
    if (count>1000) count=1000;
    for(unsigned int i=0;i<count;++i) {
        NavNode *node=QueryNodeAt(index->graph,candidates[i]);
        QueryOrder[i]=i;
        float dx=point->x-node->position.x;
        float dy=point->y-node->position.y;
        float dz=point->z-node->position.z;
        QueryDistances[i]=dx*dx+dy*dy+dz*dz;
    }
    qsort(QueryOrder,count,4,func_002FCA38);
    AuthoredProperty *property=actor->GetAuthoredProperty(&QueryHeightKey);
    float height=property?property->value:0;
    for(unsigned int i=0;i<count;++i) {
        NavNode *node=QueryNodeAt(index->graph,candidates[QueryOrder[i]]);
        if((!outgoing||node->CountOutgoing())&&(!incoming||node->CountIncoming())&&func_002E27F8(point,&node->position,actor,2,height))return node;
    }
    for(unsigned int i=0;i<count;++i) {
        NavNode *node=QueryNodeAt(index->graph,candidates[QueryOrder[i]]);
        if((!outgoing||node->CountOutgoing())&&(!incoming||node->CountIncoming()))return node;
    }
    return 0;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FBC20);
#endif
#ifdef NON_MATCHING
// Unmatched: iterator register allocation.
QueryEdge *FindNearestEdge(QueryGraph *graph,const Vec3 *point,float radius) {
    if(!QueryEdgeGuard) {
        new (&QueryEdgeStorage) NearestEdgeVisitor;
        QueryEdgeGuard=1;
        func_0035E690(func_002FCA90);
    }
    QueryEdgeStorage.point=*point;
    QueryEdgeStorage.radius=radius;
    QueryEdgeStorage.VisitEdges(graph);
    return QueryEdgeStorage.result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FC260);
#endif
#ifdef NON_MATCHING
// Unmatched: vector temporary ordering and register allocation.
void DrawGraph(QueryGraph *graph,int red,int green,int blue) {
    for(unsigned int i=0;i<graph->edgeCount;++i) {
        QueryEdge *edge=QueryEdgeAt(graph,i);
        NavNode *a=edge->EndpointA(),*b=edge->EndpointB();
        QueryVector delta=*(QueryVector*)&b->position-*(QueryVector*)&a->position;
        float length=sqrtf(func_00389140((Vec3*)&delta));
        float scale=(QueryEngine?QueryEngine->frameTime:0)*0.4f/length;
        QueryVector start=*(QueryVector*)&a->position+(delta*scale);
        QueryDrawLine(&start,(QueryVector*)&b->position,red,green,blue);
    }
    for(unsigned int i=0;i<graph->liveCount;++i) {
        NavNode *node=QueryNodeAt(graph,i);
        QueryDrawPoint((QueryVector*)&node->position,red,green,blue);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FC3C8);
#endif
#ifdef NON_MATCHING
// Unmatched: vector temporary ordering and register allocation.
void DrawGraphDefault(QueryGraph *graph) {
    for(unsigned int i=0;i<graph->edgeCount;++i) {
        QueryEdge *edge=QueryEdgeAt(graph,i);
        NavNode *a=edge->EndpointA(),*b=edge->EndpointB();
        QueryVector delta=*(QueryVector*)&b->position-*(QueryVector*)&a->position;
        float length=sqrtf(func_00389140((Vec3*)&delta));
        float scale=(QueryEngine?QueryEngine->frameTime:0)*0.4f/length;
        QueryVector start=*(QueryVector*)&a->position+(delta*scale);
        QueryDrawLine(&start,(QueryVector*)&b->position,0,0,255);
    }
    for(unsigned int i=0;i<graph->liveCount;++i) {
        NavNode *node=QueryNodeAt(graph,i);
        QueryDrawPoint((QueryVector*)&node->position,0,255,0);
    }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FC668);
#endif
void DrawPath(QueryPath *path) {
    for(int i=0;i+1<path->count;++i) {
        QueryDrawPoint(&path->points[i],0,255,255);
        if(!path->guards[i]) {
            QueryDrawLine(&path->points[i],&path->points[i+1],255,255,255);
        }else {
            QueryDrawLine(&path->points[i],&path->points[i+1],50,175,50);
        }
    }
    if(path->count)QueryDrawPoint(&path->points[path->count-1],0,255,0);
}
