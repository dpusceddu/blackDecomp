#include "game/effects/geometry.h"
#include "game/effects/random.h"
#include "game/actor/vector_math.h"
extern "C" {
extern char *D_0040F4D0,*D_0040F4D4,*D_0040F4D8;extern int *D_00414D54;extern s128 D_004432E0;
void func_001BB190(...),func_001B9B58(...),func_001B1728(s128,s128,s128 *),func_001B7A00(void *,void *,s64,int),func_001DEC08(void *,s128),func_001DED60(void *,s128,s128),func_0016E250(void *,s128,void *);
}
static inline s128 Add(s128 a,s128 b) {s128 r;__asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;}
static inline s128 Scale(s128 a,f32 scale) {s128 r,s;__asm__("qmtc2.ni fr, sv":"=j sv"(s):"r fr"(scale));__asm__("vmulx.xyz outv, av, svx":"=j outv"(r):"j av"(a),"j sv"(s));return r;}
// Unmatched: conditional impact callback widths and aggregate stack lifetimes.
#ifdef NONMATCHING
extern "C" void func_001B96B8(void *system,BkEffectGeometryPS2 *geometry,s128 position,s128 direction,char *surface,u32 a,u32 b,u32 c) {
 s128 e0=BkEffectSubPS2(geometry->points[3],geometry->points[0]),e1=BkEffectSubPS2(geometry->points[1],geometry->points[0]);
 s128 e2=BkEffectSubPS2(geometry->points[2],geometry->points[1]),e3=BkEffectSubPS2(geometry->points[2],geometry->points[3]);
 f32 sum=BkSumPS2(BkMultiplyPS2(e0,e1))+BkSumPS2(BkMultiplyPS2(e2,e1))+BkSumPS2(BkMultiplyPS2(e2,e3))+BkSumPS2(BkMultiplyPS2(e0,e3));
 bool special=__builtin_fabsf(sum)>0.01f;
 s128 normal=geometry->normal,view=BkNormalizePS2(BkEffectSubPS2(position,*(s128 *)(D_0040F4D0+0xd0)));
 if(BkEffectRandomPS2()<0.5f&&BkSumPS2(BkMultiplyPS2(normal,view))>0)normal=BkEffectSubPS2(0,normal);
 f32 size;int type=0;
 if(!surface)size=3.0f;
 else {s8 index=surface[0];type=index==-1?0:D_00414D54[index];size=type==1||type==3?0.05f:(type==4||type==5?0.1f:(type==2?0.25f:0.5f));}
 if(special||type==2)func_001BB190(system,geometry,position,direction,a,b,c,!surface?0.2f:size);
 else func_001B9B58(system,geometry,position,direction,size);
 s128 transform[4],orientation;func_001B1728(position,normal,transform);func_001B7A00(D_0040F4D8+0x696f0,transform,(s64)0x7e048c4b7c69a424ULL,1);
 func_001DEC08(&orientation,transform[3]);func_001DED60(&orientation,transform[3],D_004432E0);func_0016E250(D_0040F4D4,transform[3],surface?*(void **)(surface+0xf0):0);
}
#endif // NONMATCHING
