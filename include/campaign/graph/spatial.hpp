// PS2 class view: RTTI and vtable identity are known. Accessed graph offsets
// agree with the executable; native array initialization is checked against the loaders,
// but their source shape remains UNVERIFIED. Complete size, opaque fields and unused signatures
// remain UNVERIFIED. This campaign area is owned by the graph worker.
#ifndef BLACK_CAMPAIGN_GRAPH_SPATIAL_HPP
#define BLACK_CAMPAIGN_GRAPH_SPATIAL_HPP
#include "campaign/graph/tables.hpp"
extern "C" int _stricmp(const char*, const char*) __asm__("func_00360838");
extern "C" float sqrtf(float);
extern "C" unsigned int strlen(const char*) __asm__("func_0035CCD8");
extern char D_00407C28[], D_00407BC8[], D_00407BC0[];
namespace Kaim {
struct CSpatialGraph;
struct SpatialNode { int id; float x,y,z; CSpatialGraph *graph; SpatialNode():id(-1),graph(0){} ~SpatialNode(){} };
struct SpatialEdge { int index; CSpatialGraph *graph; SpatialEdge():index(-1),graph(0){} ~SpatialEdge(){} inline SpatialNode *EndNode(); inline SpatialNode *StartNode(); };
struct CSpatialGraph : CObject {
 static void *operator new(unsigned int size){return Allocate(size);}
 CSpatialGraph() __asm__("func_002F5C10");
 virtual ~CSpatialGraph();
 virtual bool LoadOld(FileService*,const void*);
 virtual bool Load(const void*);
 virtual bool LoadFromPath(const char*);
 virtual bool SaveOld(const void*);
 virtual bool Write(const void*,unsigned int);
 virtual void Reset();
 unsigned int flags;
 union { unsigned int field08; float coverageDistance; };
 unsigned int nodeCapacity,nodeSlots,nodeCount;
 SpatialNode *nodes; int *nodeTable1c,*firstEdgeFrom,*firstEdgeTo;
 union { unsigned int field28; unsigned int edgeCapacity; };
 unsigned int edgeSlots,edgeCount;
 SpatialEdge *edges; int *edgeEnd,*edgeStart,*edgeTable40,*edgeNext,*edgeTable48,*edgeTable4c,*edgeTable50;
 unsigned char unknown54[8]; SpatialEdge syntheticEdge; SpatialNode syntheticEnd,syntheticStart;
 unsigned char unknown8c[12];
 inline unsigned char HasFlag(unsigned int flag){if(flags&flag)return 1;return 0;}
 inline unsigned int NodeCount(){return nodeCount;}
 void Compact() __asm__("func_002FA4C8");
 void SetFlags(unsigned int) __asm__("func_002FA930");
 SpatialEdge *FindEdge(unsigned int,unsigned int);
 inline SpatialNode *GetNode(unsigned int n) { if(n>=nodeCapacity)return 0; SpatialNode *p=nodes+n;return p->id==-1?0:p; }
 inline SpatialEdge *GetEdge(unsigned int n) { if(n>=edgeCapacity)return 0; SpatialEdge *p=edges+n;return p->index==-1?0:p; }
};
inline SpatialNode *SpatialEdge::EndNode(){CSpatialGraph *owner=graph;if(this==&owner->syntheticEdge)return &owner->syntheticEnd;return &owner->nodes[owner->edgeEnd[index]];}
inline SpatialNode *SpatialEdge::StartNode(){CSpatialGraph *owner=graph;if(this==&owner->syntheticEdge)return &owner->syntheticStart;return &owner->nodes[owner->edgeStart[index]];}
struct ConfigBlock {
 unsigned char data[0x24];
 ConfigBlock() __asm__("func_002E3408");
 ConfigBlock *SetSecond(const char*) __asm__("func_002E3630");
 ConfigBlock *SetThird(const char*) __asm__("func_002E36E8");
 static void *operator new(unsigned int size){return Allocate(size);}
 static void operator delete(void*p){D_003C87E0(p);}
};
struct ArenaAllocator : Allocator { unsigned char data[0x1c]; ArenaAllocator(void*,unsigned int,int,unsigned int) __asm__("func_002E5C38"); ~ArenaAllocator(); };
struct PathFileService : FileService { PathFileService() __asm__("func_00373250"); ~PathFileService(); };
inline void Word_Convert(unsigned int*out,const unsigned int*in,int){*out=*in;}
struct GraphVisitor : CObject {
 virtual ~GraphVisitor(){} virtual void Begin(CSpatialGraph*) __asm__("func_003915C0"); virtual void BeginEdges(CSpatialGraph*) __asm__("func_003915C8");
 virtual bool Consider(SpatialNode*){return true;} virtual bool Accept(SpatialEdge*){return true;}
 inline bool VisitNodes(CSpatialGraph *graph){Begin(graph);unsigned int seen=0,slot=0;while(seen<graph->nodeCount){SpatialNode *node=graph->GetNode(slot);if(node){++seen;if(!Consider(node))return false;}++slot;}return true;}
 inline bool VisitAll(CSpatialGraph *graph){BeginEdges(graph);unsigned int seen=0,slot=0;while(seen<graph->edgeCount){SpatialEdge *edge=graph->GetEdge(slot);if(edge){++seen;if(!Accept(edge))return false;}++slot;}return true;}
};
struct GraphWriter : GraphVisitor { virtual ~GraphWriter(){} void *file; int byteOrder; virtual bool Consider(SpatialNode*);virtual bool Accept(SpatialEdge*); };
}


#define SPATIAL_OFFSET(member, offset) typedef char Spatial_##member##_offset[(unsigned int)&((Kaim::CSpatialGraph *)0)->member == offset ? 1 : -1]
SPATIAL_OFFSET(flags,4);
SPATIAL_OFFSET(coverageDistance,8);
SPATIAL_OFFSET(nodes,0x18);
SPATIAL_OFFSET(edges,0x34);
SPATIAL_OFFSET(syntheticEdge,0x5c);
SPATIAL_OFFSET(syntheticEnd,0x64);
SPATIAL_OFFSET(syntheticStart,0x78);
typedef char SpatialGraphAllocationSize[sizeof(Kaim::CSpatialGraph)==0x98?1:-1];
#undef SPATIAL_OFFSET
#endif
