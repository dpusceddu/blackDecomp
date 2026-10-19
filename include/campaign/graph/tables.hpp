#ifndef BLACK_CAMPAIGN_GRAPH_TABLES_HPP
#define BLACK_CAMPAIGN_GRAPH_TABLES_HPP
#include "kynapse/point_mapper.hpp"
#include "classes/kynapse/Kaim_CPathCostData.hpp"
#include "classes/kynapse/Kaim_CAstarData.hpp"

inline void *operator new[](unsigned int size) { return Allocate(size); }

// PS2 offset views checked against the graph/table access instructions. The
// generated RTTI interfaces remain the owner of class identity and slot evidence.
// Complete object sizes, opaque bytes, and unused virtual signatures remain
// UNVERIFIED. Only the accessed prefixes and asserted member offsets are modeled.
namespace Kaim {
struct SearchGraph;
struct SearchNode { unsigned int id; float x, y, z; SearchGraph *graph; };
struct SearchEdge { int index; SearchGraph *graph; };
struct RouteBuffers {
    unsigned char unknown00[8];
    unsigned int count;
    unsigned char unknown0c[4];
    unsigned int *edgeIds;
    unsigned char unknown14[0x14];
    RouteBuffers() __asm__("func_002FB558");
    ~RouteBuffers();
    void Reserve(int) __asm__("func_002FB1C8");
    inline void Clear() { count = 0; *(int *)((char *)this + 0x24) = 0; }
};
struct SearchGraph {
    unsigned char unknown00[0xc];
    unsigned int nodeCapacity;
    unsigned char unknown10[4];
    int liveNodes;
    SearchNode *nodes;
    unsigned char unknown1c[0xc];
    unsigned int edgeCapacity;
    unsigned int edgeSlots, edgeCount;
    SearchEdge *edges;
    unsigned char unknown38[0x14];
    float *edgeLengths;
    unsigned char unknown50[4];
    void *costPolicy, *heuristic;
    SearchEdge syntheticEdge;
    unsigned char unknown64[0x2c];
    float syntheticLength;
    int FindRoute(RouteBuffers *, SearchNode *, SearchNode *, void *) __asm__("func_002EE078");
    inline SearchNode *GetNode(unsigned int n) { if (n >= nodeCapacity) return 0; SearchNode *p = nodes+n; return p->id == (unsigned int)-1 ? 0 : p; }
    inline SearchEdge *GetEdge(unsigned int n) { if (n >= edgeCapacity) return 0; SearchEdge *p = edges+n; return p->index == -1 ? 0 : p; }
};
// These placeholders preserve the observed temporary policy lifetimes. Their
// complete inheritance and unused virtual signatures remain unverified.
struct DefaultBase { virtual ~DefaultBase() {} };
struct DefaultCostPolicy : DefaultBase { virtual ~DefaultCostPolicy() {} };
struct DefaultHeuristic : DefaultBase { virtual ~DefaultHeuristic() {} };
struct CObject {
    virtual ~CObject() {}
    static void operator delete(void *p) { D_003C87E0(p); }
};
struct CGraphData : CObject {
    virtual ~CGraphData() {}
    virtual int Init(ChildBuffers *);
    virtual void *GetClassInfo();
    virtual int Build();
    virtual int Save(const void *);
    SearchGraph *graph;
};
struct CPathCostData : CGraphData {
    virtual ~CPathCostData();
    virtual int Init(ChildBuffers *);
    virtual int Build();
    virtual int Save(const void *);
    unsigned char *table;
    int size;
    float scale;
    void (*progress)(int, int, float, int);
};
struct CAstarData : CGraphData {
    virtual ~CAstarData();
    virtual int Init(ChildBuffers *);
    virtual int Build();
    virtual int Save(const void *);
    int count;
    int **rows;
    void (*progress)(int);
    bool Load(const void *) __asm__("func_002FDBA8");
};
}
#define GRAPH_OFFSET(type, member, offset) typedef char type##_##member##_offset[(unsigned int)&((type *)0)->member == offset ? 1 : -1]
namespace Kaim {
GRAPH_OFFSET(CGraphData, graph, 4);
GRAPH_OFFSET(CPathCostData, table, 8);
GRAPH_OFFSET(CPathCostData, size, 12);
GRAPH_OFFSET(CPathCostData, scale, 16);
GRAPH_OFFSET(CPathCostData, progress, 20);
GRAPH_OFFSET(CAstarData, count, 8);
GRAPH_OFFSET(CAstarData, rows, 12);
GRAPH_OFFSET(CAstarData, progress, 16);
GRAPH_OFFSET(SearchGraph, nodes, 0x18);
GRAPH_OFFSET(SearchGraph, edges, 0x34);
GRAPH_OFFSET(SearchGraph, edgeLengths, 0x4c);
GRAPH_OFFSET(SearchGraph, costPolicy, 0x54);
GRAPH_OFFSET(SearchGraph, heuristic, 0x58);
}
#undef GRAPH_OFFSET
#endif
