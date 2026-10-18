#include "game/effects/geometry.h"
#include "game/effects/pool.h"
#include "game/effects/random.h"
#include "game/actor/vector_math.h"
extern "C" {
extern char *D_0040F4D0,*D_0040F4D8;extern BkEffectVectorPS2 D_004432E0;
extern void func_001BB190(void *,BkEffectGeometryPS2 *,s128,s128,void *,int,int,f32);
extern void func_001B1728(s128,s128,BkEffectVectorPS2 *),func_001DED60(void *,s128,s128);
extern void func_001B7A00(void *,void *,s64,int);
}
// Unmatched: mixed 128-bit point arguments and temporary transform scheduling.
#ifdef NONMATCHING
extern "C" void func_001B8798(void *system,BkEffectGeometryPS2 *geometry,BkEffectBatchPS2 *batch,int index,int kind) {
 f32 t=BkEffectRandomPS2()*0.8f+0.1f;
 BkEffectVectorPS2 point,direction,normal=geometry->normal,transform[4];
 BkEffectVectorPS2 a=geometry->points[0],b=geometry->points[2],weight;
 __asm__("qmtc2.ni scalarr, weightv":"=j weightv"(weight):"r scalarr"(t));
 __asm__("vaddax.xyz ACC, av, vf0x\n\tvmsubax.xyz ACC, av, weightvx\n\tvmaddx.xyz outv, bv, weightvx":"=j outv"(point):"j av"(a),"j bv"(b),"j weightv"(weight));
 direction=BkNormalizePS2(BkEffectSubPS2(point,*(BkEffectVectorPS2 *)(D_0040F4D0+0xd0)));
 if(BkSumPS2(BkMultiplyPS2(normal,direction))>0.0f)normal=BkEffectSubPS2(0,normal);
 func_001BB190(system,geometry,point,direction,batch->material,((batch->flags>>1)^1)&1,kind,0.0f);
 batch->enabled[index/8]&=~(1<<(index%8));
 func_001B1728(point,normal,transform);
 func_001B7A00(D_0040F4D8+0x696f0,transform,(s64)0x7e048c4b7c69a424ULL,1);
 func_001DED60(transform+4,transform[3],D_004432E0);
}
#endif // NONMATCHING
