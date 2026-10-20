// Unmatched: native receiver and iterator/store lifetimes remain inexact.
#ifdef NONMATCHING
#include "mod/effects/runtime.hpp"
#include "game/effects/geometry.h"
#include "game/effects/pool.h"
using ModEffects::Matrix;
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
int PoolMethods::Queue(void *definition,const Matrix *transform,long mode){
 if(pendingCount==256)return 0;
 Matrix temporary;
 if(mode==0){ModEffects::IdentityXYZ(temporary);temporary.row[3]=transform->row[3];}
 else if(mode==1)temporary=*transform;
 Pending *slot=(Pending*)((char*)this+0x15000)+pendingCount;
 slot->matrix=temporary;
 ((Pending*)((char*)this+0x15000))[pendingCount].definition=definition;
 pendingCount++;return 1;
}
#endif
