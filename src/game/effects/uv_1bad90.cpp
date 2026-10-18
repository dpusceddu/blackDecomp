// Unmatched: UV temporary lifetimes and scalar scheduling.
#ifdef NONMATCHING
#include "game/effects/vector.h"
extern "C" void func_001BAD90(BkEffectUVPS2 *out,const BkEffectVectorPS2 *points,const BkEffectVectorPS2 *triangle,const BkEffectUVPS2 *uv,int count) {
 BkEffectPointPS2 edge2=BkEffectSpillPS2(BkEffectSubPS2(triangle[2],triangle[0]));
 BkEffectPointPS2 edge1=BkEffectSpillPS2(BkEffectSubPS2(triangle[1],triangle[0]));
 union {f32 f;u32 u;} determinant;
 f32 scale;BkEffectUVPS2 base=uv[0],du,dv;
 du.u=uv[2].u-base.u;du.v=uv[2].v-base.v;dv.u=uv[1].u-base.u;dv.v=uv[1].v-base.v;
 determinant.f=edge2.z*edge1.x-edge2.x*edge1.z;
 scale=(determinant.u&0x7f800000)<=0x37800000?1.0f:1.0f/determinant.f;
 du.u*=scale;du.v*=scale;dv.u*=scale;dv.v*=scale;
 while(count>0) {
  BkEffectPointPS2 delta=BkEffectSpillPS2(BkEffectSubPS2(*points++,triangle[0]));
  f32 a=delta.z*edge1.x-delta.x*edge1.z,b=delta.x*edge2.z-delta.z*edge2.x;
  out->u=base.u+du.u*a+dv.u*b;out->v=base.v+du.v*a+dv.v*b;out++;count--;
 }
}

#endif // NONMATCHING
