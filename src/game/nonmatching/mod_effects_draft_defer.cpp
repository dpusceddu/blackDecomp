// Unmatched: native receiver and iterator/store lifetimes remain inexact.
#ifdef NONMATCHING
#include "game/effects/runtime.hpp"
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
extern "C" {void func_001C3E10(),func_001C4130(int),func_001B7FC8(void*,int),func_001B82E0(void*,int),func_001C45C0(),func_001C45E0(),func_001B7F08(void*),func_001B8138(void*),func_001C3E08();}
struct SimulationMethods{int count;char pad[12];BkEffectGeometryPS2 records[255];void*pending[32];void*batches[32];float scales[32];short indices[32];float timeout[32];unsigned char kinds[32],next;void Render() __asm__("func_001B86F8");int Clear() __asm__("func_001B90D0");void Defer(float,float,BkEffectGeometryPS2*,void*,short,unsigned char) __asm__("func_001B9A40");};
extern "C" void func_001B8798(void*,BkEffectGeometryPS2*,void*,short,unsigned char,float);
void SimulationMethods::Defer(float scale,float duration,BkEffectGeometryPS2*geometry,void*batch,short index,unsigned char kind){if(scale>0.15f){if(!(*(unsigned short*)((char*)batch+6)&1)||((float*)geometry)[3]<0.8f)func_001B8798(this,geometry,batch,index,kind,scale);else{pending[next]=geometry;timeout[next]=duration*0.15f;batches[next]=batch;indices[next]=index;scales[next]=scale;kinds[next]=kind;next++;if(next==32)next=0;BkEffectPointPS2 v=BkEffectSpillPS2(geometry->normal);v.w=-999.9f;geometry->normal=*(s128*)&v;}}}
#endif
