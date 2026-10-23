#include "game/effects/geometry.h"
#include "game/effects/random.h"
#include "game/actor/vector_math.h"
extern BkEffectVectorPS2 D_004159E0,D_004432C0;extern int D_004159F0;
static inline s128 Add(s128 a,s128 b) {s128 r;__asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;}
static inline s128 Scale(s128 a,f32 scale) {s128 r,s;__asm__("qmtc2.ni fr, sv":"=j sv"(s):"r fr"(scale));__asm__("vmulx.xyz outv, av, svx":"=j outv"(r):"j av"(a),"j sv"(s));return r;}
static inline f32 Magnitude(s128 a) {
 s128 sum,one=BkOnePS2(),square=BkMultiplyPS2(a,a),result;f32 value;
 __asm__("vadday.x ACC, sqv, sqvy\n\tvmaddz.x sumv, onev, sqvz":"=j sumv"(sum):"j sqv"(square),"j onev"(one));
 __asm__("vnop\n\tvnop\n\tvnop\n\tvsqrt Q, sumvx\n\tvaddw.x outv, vf0, vf0w\n\tvwaitq\n\tvmulq.x outv, outv, Q":"=j outv"(result):"j sumv"(sum));
 __asm__("qmfc2.ni vr, vv":"=r vr"(value):"j vv"(result));return value;
}
// Unmatched: VU centroid/minimum lanes, random-axis lifetimes and wide argument allocation.
#ifdef NONMATCHING
extern "C" void func_001B9198(BkEffectGeometryPS2 *geometry,s128 normal,s128 velocity,s8 count,s16 tag,void *material,u8 pass,u8 flags,s128 direction,f32 lifetime,f32 size) {
 BkEffectPointPS2 gravity={0,-0.01f,0,0},identity[4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,0}};
 if(!D_004159F0) {D_004159E0=*(s128 *)&gravity;D_004159F0=1;}
 geometry->material=material;geometry->pass=pass;geometry->flags=flags;geometry->vertexCount=count;
 if(count==3) {geometry->uv[3].u=0;geometry->uv[3].v=0;geometry->points[3]=0;}
 s128 center=0,minimum;BkEffectPointPS2 maximum={3.4028235e38f,3.4028235e38f,3.4028235e38f,0};minimum=*(s128 *)&maximum;
 for(int i=count,j=0;i>0;i--,j++) {
  s128 point=geometry->points[j];__asm__("vmini.xyz outv, av, bv":"=j outv"(minimum):"j av"(minimum),"j bv"(point));center=Add(center,point);
 }
 for(int i=0;i<4;i++)geometry->transform[i]=*(s128 *)&identity[i];
 center=Scale(center,1.0f/(f32)count);
 __asm__("vaddy.y outv, vf0, minvy":"+j outv"(center):"j minv"(minimum));geometry->transform[3]=center;
 for(int i=0;i<geometry->vertexCount;i++)geometry->points[i]=BkEffectSubPS2(geometry->points[i],geometry->transform[3]);
 normal=BkEffectSubPS2(0,normal);geometry->normal=normal;geometry->velocity=velocity;geometry->gravity=D_004159E0;
 geometry->tag=tag;geometry->frames=80;geometry->lifetime=lifetime;geometry->elapsed=0;geometry->unknownFC=0;
 s128 axis=BkCrossPS2(D_004432C0,normal);
 if(BkSumPS2(BkMultiplyPS2(axis,axis))<2.3283064e-10f) {
  geometry->size=(BkEffectRandomPS2()+1.0f)*10.0f;
  BkEffectPointPS2 randomAxis={1.0f-2.0f*BkEffectRandomPS2(),0.25f,1.0f-2.0f*BkEffectRandomPS2(),0};geometry->direction=BkNormalizePS2(*(s128 *)&randomAxis);
 }else {
  union {f32 f;u32 u;} test;test.f=size;
  if((test.u&0x7f800000)<=0x37800000) {geometry->direction=axis;geometry->size=0;}
  else {geometry->direction=direction;geometry->size=size;}
 }
 if(geometry->vertexCount==3) {
  s128 a=BkEffectSubPS2(geometry->points[2],geometry->points[0]),b=BkEffectSubPS2(geometry->points[1],geometry->points[0]);geometry->area=Magnitude(BkCrossPS2(a,b))*0.5f;
 }else if(geometry->vertexCount==4) {
  s128 a=BkEffectSubPS2(geometry->points[2],geometry->points[0]),b=BkEffectSubPS2(geometry->points[1],geometry->points[0]);
  s128 c=BkEffectSubPS2(geometry->points[2],geometry->points[3]),d=BkEffectSubPS2(geometry->points[1],geometry->points[3]);
  geometry->area=(Magnitude(BkCrossPS2(a,b))+Magnitude(BkCrossPS2(c,d)))*0.5f;
 }
}
#endif // NONMATCHING
