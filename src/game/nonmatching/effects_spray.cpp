#include "game/effects/geometry.h"
#include "game/effects/random.h"
#include "game/actor/vector_math.h"
extern "C" { extern char *D_0040F4D8;void func_001B1728(s128,s128,BkEffectVectorPS2 *);void func_001B7A00(void *,void *,s64,int); }
static inline s128 Add(s128 a,s128 b) {s128 r;__asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;}
static inline s128 Scale(s128 a,f32 scale) {s128 r,s;__asm__("qmtc2.ni fr, sv":"=j sv"(s):"r fr"(scale));__asm__("vmulx.xyz outv, av, svx":"=j outv"(r):"j av"(a),"j sv"(s));return r;}
// Unmatched: orthogonal basis spills and interleaved random-state updates.
#ifdef NONMATCHING
extern "C" void func_001BC548(void *,s128 position,s128 normal,int count,f32 width,f32 height) {
 BkEffectPointPS2 n=BkEffectSpillPS2(normal),axis;
 if(n.y>0.9f) {axis.x=1;axis.y=0;axis.z=0;axis.w=0;}
 else if(n.y < -0.9f) {axis.x=-1;axis.y=0;axis.z=0;axis.w=0;}
 else {axis.x=0;axis.y=0;axis.z=1;axis.w=0;}
 s128 right=BkNormalizePS2(BkCrossPS2(*(s128 *)&axis,normal)),up=BkCrossPS2(normal,right);
 for(;count>0;count--) {
  f32 x=BkEffectRandomPS2()-0.5f,y=BkEffectRandomPS2()-0.5f;
  s128 direction=BkNormalizePS2(Add(Add(normal,Scale(up,0.7f*x)),Scale(right,0.7f*y)));
  s128 point=Add(position,Add(Add(Scale(up,width*x),Scale(right,height*y)),Scale(normal,0.0f)));
  BkEffectVectorPS2 transform[4];func_001B1728(point,direction,transform);
  func_001B7A00(D_0040F4D8+0x696f0,transform,(s64)0x7e048c4b7c69a423ULL,1);
 }
}
#endif // NONMATCHING
