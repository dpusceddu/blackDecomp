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
void PoolMethods::Stop(){struct Book {unsigned short *indices,*reverse;unsigned short activeCount;};Book *book=(Book*)((char*)this+0x1a000);unsigned short remaining=book->activeCount-1,*cursor=book->indices;while(remaining!=65535){BkEffectEntryPS2 *entry=entries+*cursor;if(func_001B16A8(entry))func_001B15A0(entry);--remaining;++cursor;}}
#endif
