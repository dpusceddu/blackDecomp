// PS2 accessways prefix and its traversal helpers. Slots come from RTTI/vtables;
// unused signatures and full traversal layouts remain UNVERIFIED.
#ifndef BLACK_CAMPAIGN_GRAPH_ACCESSWAYS_HPP
#define BLACK_CAMPAIGN_GRAPH_ACCESSWAYS_HPP
#include "kynapse/graph/spatial.hpp"
extern "C" void *memset(void*,int,unsigned int);
extern "C" void *memcpy(void*,const void*,unsigned int);
extern char D_00407DB8[];
extern const unsigned int D_00407DD0;
extern Vec3 D_004514F8;
struct AccessHooks {
 unsigned char unknown00[0x54];void *(*open)(const void*,const char*);void(*close)(void*);unsigned char unknown5c[8];
 unsigned int (*write)(const void*,unsigned int,unsigned int,void*);
 unsigned int (*read)(void*,unsigned int,unsigned int,void*);
};
extern AccessHooks AccessFile __asm__("D_00451228");
namespace Kaim {
struct CAccessWaysData : CGraphData {
 CAccessWaysData(SearchGraph*) __asm__("func_002FD7D8");
 virtual ~CAccessWaysData();
 virtual int Init(ChildBuffers*);virtual int Build();virtual int Save(const void*);
 short **lists;short *counts;short nodeCount;void(*progress)(unsigned int);
 int Load(const void*) __asm__("func_002FCEC0");
 int LoadFile(const void*) __asm__("func_002FCB50");
 int Get(int,short**) __asm__("func_002FD908");
 static void *operator new(unsigned int n){return Allocate(n);}
};
}
struct ComputeAccessWaysTraversal : Kaim::GraphVisitor {
 Kaim::CSpatialGraph *graph;Kaim::CAccessWaysData *owner;
 ComputeAccessWaysTraversal(){}
 virtual void Begin(Kaim::CSpatialGraph*g){graph=g;}
 virtual bool Consider(Kaim::SpatialNode*);
};
struct ComputeVisibilityTraversal : Kaim::GraphVisitor {
 Vec3 origin;Kaim::CAccessWaysData *owner;char *flags;short *values;short count;
 ComputeVisibilityTraversal(){origin.x=D_004514F8.x;origin.y=D_004514F8.y;origin.z=D_004514F8.z;flags=0;values=0;count=0;}
 virtual ~ComputeVisibilityTraversal(){if(flags){D_003C87E0(flags);flags=0;}if(values){D_003C87E0(values);values=0;}}
 virtual void Begin(Kaim::CSpatialGraph*);virtual void BeginEdges(Kaim::CSpatialGraph*);virtual bool Consider(Kaim::SpatialNode*);virtual bool Accept(Kaim::SpatialEdge*);
};


#define ACCESS_OFFSET(member, offset) typedef char Access_##member##_offset[(unsigned int)&((Kaim::CAccessWaysData*)0)->member==offset?1:-1]
ACCESS_OFFSET(lists,8); ACCESS_OFFSET(counts,12); ACCESS_OFFSET(nodeCount,16); ACCESS_OFFSET(progress,20);
typedef char AccessAllocationSize[sizeof(Kaim::CAccessWaysData)==24?1:-1];
#undef ACCESS_OFFSET
#endif
