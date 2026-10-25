#include "include_asm.h"

#include "game/effects/simulation.hpp"

void Effects::GeometryNodes::Clear(){int i=11;BkEffectGeometryBucketPS2**p=heads;do{((void**)p)[-12]=0;--i;*p++=0;}while(i>=0);BkEffectGeometryBucketPS2*b=nodes,*end=nodes+8;do{b->count=0;b->next=0;b++;}while((int)b<(int)end);}

#ifdef NON_MATCHING
// Unmatched: native receiver and iterator/store lifetimes remain inexact.
#include "game/effects/runtime.hpp"
#include "game/effects/geometry.h"
#include "game/effects/pool.h"
using Effects::Matrix;
extern "C" {extern char *D_0040F4D8,*D_0040F4D4;}
struct NodeManager {
 BkEffectGeometryBucketPS2 nodes[8]; void*materials[12];BkEffectGeometryBucketPS2*heads[12];
 void Clear() __asm__("func_001B8138");
 BkEffectGeometryBucketPS2 *Free(int) __asm__("func_001B82B0");
 void Add(BkEffectGeometryPS2*) __asm__("func_001B8180");
};
struct PoolMethods: BkEffectPoolPS2 {
 int Queue(void*,const Matrix*,long) __asm__("func_001B7A70");
 void Stop() __asm__("func_001B7E60");
};
extern "C" int func_001B16A8(BkEffectEntryPS2*);extern "C" void func_001B15A0(BkEffectEntryPS2*);
struct Pending {Matrix matrix;void*definition;char pad[12];};
void NodeManager::Add(BkEffectGeometryPS2*geometry){int i=0;void**material=materials;do{
 if(!*material){BkEffectGeometryBucketPS2*b=Free(i);if(!b)return;heads[i]=b;*material=geometry->material;b->records[b->count]=geometry;b->count++;return;}
 if(*material==geometry->material){BkEffectGeometryBucketPS2*b=heads[i];while(b->next)b=b->next;if(b->count<32){b->records[b->count]=geometry;b->count++;}else{BkEffectGeometryBucketPS2*next=Free(i);if(next){b->next=next;next->records[next->count]=geometry;next->count++;}}return;}
 i++;material++;
 }while(i<12);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B8180);
#endif
