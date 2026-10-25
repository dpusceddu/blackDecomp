#include "include_asm.h"

#include "game/effects/simulation.hpp"
extern "C" {void func_001C3E10(),func_001C4130(int),func_001B7FC8(void*,int),func_001B82E0(void*,int),func_001C45C0(),func_001C45E0(),func_001B7F08(void*),func_001B8138(void*),func_001C3E08();}

int Effects::Simulation::Clear(){count=0;func_001B7F08((char*)this+0x11604);func_001B8138((char*)this+0x11164);func_001C3E08();unsigned short i=0;do{pending[i]=0;batches[i]=0;indices[i]=-1;timeout[i]=0;scales[i]=0;kinds[i]=0;i++;next=0;}while(i<32);return 1;}

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B9198);
#endif

#ifdef NON_MATCHING
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B96B8);
#endif

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
extern "C" {void func_001C3E10(),func_001C4130(int),func_001B7FC8(void*,int),func_001B82E0(void*,int),func_001C45C0(),func_001C45E0(),func_001B7F08(void*),func_001B8138(void*),func_001C3E08();}
struct SimulationMethods{int count;char pad[12];BkEffectGeometryPS2 records[255];void*pending[32];void*batches[32];float scales[32];short indices[32];float timeout[32];unsigned char kinds[32],next;void Render() __asm__("func_001B86F8");int Clear() __asm__("func_001B90D0");void Defer(float,float,BkEffectGeometryPS2*,void*,short,unsigned char) __asm__("func_001B9A40");};
extern "C" void func_001B8798(void*,BkEffectGeometryPS2*,void*,short,unsigned char,float);
void SimulationMethods::Defer(float scale,float duration,BkEffectGeometryPS2*geometry,void*batch,short index,unsigned char kind){if(scale>0.15f){if(!(*(unsigned short*)((char*)batch+6)&1)||((float*)geometry)[3]<0.8f)func_001B8798(this,geometry,batch,index,kind,scale);else{pending[next]=geometry;timeout[next]=duration*0.15f;batches[next]=batch;indices[next]=index;scales[next]=scale;kinds[next]=kind;next++;if(next==32)next=0;BkEffectPointPS2 v=BkEffectSpillPS2(geometry->normal);v.w=-999.9f;geometry->normal=*(s128*)&v;}}}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B9A40);
#endif

#ifdef NON_MATCHING
// Unmatched: twenty-fragment UV workspace, table-owned tags and scalar/VU temporary lifetimes.
#include "game/effects/fracture.h"
extern s8 D_003F7490[20][5];extern s128 D_004432A0,D_004432C0;
extern "C" void func_001B9B58(BkEffectFracturePoolPS2 *pool,BkEffectGeometryPS2 *source,s128 point,s128 incoming,void *material,int pass,int flags,f32 scale) {
 if(pool->count>=254){func_001BC548(pool,point,incoming,0,0,0,0.3f,0.3f);return;}
 s128 normal=source->normal;if(BkSumPS2(BkMultiplyPS2(normal,BkNormalizePS2(incoming)))>0)normal=BkEffectSubPS2(0,normal);
 BkEffectPointPS2 delta=BkEffectSpillPS2(BkEffectSubPS2(point,source->points[0])),diagonal=BkEffectSpillPS2(BkEffectSubPS2(source->points[2],source->points[0])),p=BkEffectSpillPS2(point);
 f32 lifetime=p.y-3-BkEffectRandomPS2()*12,cx,cy;union{f32 f;u32 u;} x,y;x.f=diagonal.x;y.f=diagonal.y;
 if((y.u&0x7f800000)<=0x37800000){cx=delta.x/diagonal.x;cy=delta.z/diagonal.z;}
 else if((x.u&0x7f800000)<=0x37800000){cx=delta.z/diagonal.z;cy=delta.y/diagonal.y;}
 else{cx=delta.x/diagonal.x;cy=delta.y/diagonal.y;}
 BkEffectUVPS2 uv[20]={{0,0},{0,1},{1,1},{1,0}};
 uv[4].u=(BkEffectRandomPS2()*0.8f+0.1f)*cx;uv[4].v=0;
 uv[5].u=cx+(BkEffectRandomPS2()*0.8f+0.1f)*(1-cx);uv[5].v=0;
 uv[6].u=1;uv[6].v=(BkEffectRandomPS2()*0.8f+0.1f)*cy;
 uv[7].u=1;uv[7].v=cy+(BkEffectRandomPS2()*0.8f+0.1f)*(1-cy);
 uv[8].u=cx+(BkEffectRandomPS2()*0.8f+0.1f)*(1-cx);uv[8].v=1;
 uv[9].u=(BkEffectRandomPS2()*0.8f+0.1f)*cx;uv[9].v=1;
 uv[10].u=0;uv[10].v=cy+(BkEffectRandomPS2()*0.8f+0.1f)*(1-cy);
 uv[11].u=0;uv[11].v=(BkEffectRandomPS2()*0.8f+0.1f)*cy;
 f32 fraction=BkEffectRandomPS2()*scale,contraction=fraction*0.6f+(1-fraction)*0.3f;
 for(int i=12;i<20;i++){uv[i].u=cx+(uv[i-8].u-cx)*contraction;uv[i].v=cy+(uv[i-8].v-cy)*contraction;}
 s128 points[20],uEdge=BkEffectSubPS2(source->points[3],source->points[0]),vEdge=BkEffectSubPS2(source->points[1],source->points[0]);
 for(int i=0;i<20;i++)points[i]=BkEffectAddPS2(BkEffectAddPS2(source->points[0],BkEffectScalePS2(uEdge,uv[i].u)),BkEffectScalePS2(vEdge,uv[i].v));
 BkEffectUVPS2 base=source->uv[0],uDelta={source->uv[3].u-base.u,source->uv[3].v-base.v},vDelta={source->uv[1].u-base.u,source->uv[1].v-base.v};u32 tags[8];
 for(int i=19;i>=0;i--) {
  BkEffectGeometryPS2 *geometry=BkEffectAllocateGeometryPS2(pool);if(!geometry)return;
  for(int j=0;j<4;j++){int k=D_003F7490[i][j];geometry->points[j]=points[k];geometry->uv[j].u=base.u+uDelta.u*uv[k].u+vDelta.u*uv[k].v;geometry->uv[j].v=base.v+uDelta.v*uv[k].u+vDelta.v*uv[k].v;}
  f32 random=BkEffectRandomPS2();u32 bits=D_00418590[0];s16 tag=0;s128 direction=D_004432C0,velocity=D_004432A0;f32 spin=0;
  if(i>=12){tags[i&7]=((bits&15)==0)?((bits>>2)&10):((bits>>2)&5);direction=BkNormalizePS2(BkEffectSubPS2(geometry->points[1],geometry->points[0]));velocity=BkEffectScalePS2(BkCrossPS2(normal,direction),0.03f);BkEffectPointPS2 motion=BkEffectSpillPS2(velocity);motion.y+=0.01f;velocity=*(s128 *)&motion;spin=8;tag=(s16)(BkEffectRandomPS2()*10);}
  else if(i>=4){tags[i&7]+=((bits&7)==0)?((bits>>2)&15):((bits>>2)&3);tag=(s16)(tags[i&7]+(int)(BkEffectRandomPS2()*15));}
  else {tag=(s16)(tags[(2*((i-1)&3)+5)&7]+((bits&1)?(bits&15):(bits&7)));BkEffectRandomPS2();}
  func_001B9198(geometry,normal,velocity,D_003F7490[i][4],tag,material,(u8)pass,(u8)flags,direction,lifetime,spin);
  if(geometry->area<0.007f){pool->count--;if(geometry!=pool->records+pool->count)*geometry=pool->records[pool->count];}
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B9B58);
#endif

#ifdef NON_MATCHING
// Unmatched: UV temporary lifetimes and scalar scheduling.
#include "game/effects/vector.h"
extern "C" void func_001BAB90(BkEffectUVPS2 *out,const BkEffectVectorPS2 *points,const BkEffectVectorPS2 *triangle,const BkEffectUVPS2 *uv,int count) {
 BkEffectPointPS2 edge2=BkEffectSpillPS2(BkEffectSubPS2(triangle[2],triangle[0]));
 BkEffectPointPS2 edge1=BkEffectSpillPS2(BkEffectSubPS2(triangle[1],triangle[0]));
 union {f32 f;u32 u;} determinant;
 f32 scale;BkEffectUVPS2 base=uv[0],du,dv;
 du.u=uv[2].u-base.u;du.v=uv[2].v-base.v;dv.u=uv[1].u-base.u;dv.v=uv[1].v-base.v;
 determinant.f=edge2.y*edge1.x-edge2.x*edge1.y;
 scale=(determinant.u&0x7f800000)<=0x37800000?1.0f:1.0f/determinant.f;
 du.u*=scale;du.v*=scale;dv.u*=scale;dv.v*=scale;
 while(count>0) {
  BkEffectPointPS2 delta=BkEffectSpillPS2(BkEffectSubPS2(*points++,triangle[0]));
  f32 a=delta.y*edge1.x-delta.x*edge1.y,b=delta.x*edge2.y-delta.y*edge2.x;
  out->u=base.u+du.u*a+dv.u*b;out->v=base.v+du.v*a+dv.v*b;out++;count--;
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BAB90);
#endif

#ifdef NON_MATCHING
// Unmatched: UV temporary lifetimes and scalar scheduling.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BAD90);
#endif

#ifdef NON_MATCHING
// Unmatched: UV temporary lifetimes and scalar scheduling.
#include "game/effects/vector.h"
extern "C" void func_001BAF90(BkEffectUVPS2 *out,const BkEffectVectorPS2 *points,const BkEffectVectorPS2 *triangle,const BkEffectUVPS2 *uv,int count) {
 BkEffectPointPS2 edge2=BkEffectSpillPS2(BkEffectSubPS2(triangle[2],triangle[0]));
 BkEffectPointPS2 edge1=BkEffectSpillPS2(BkEffectSubPS2(triangle[1],triangle[0]));
 union {f32 f;u32 u;} determinant;
 f32 scale;BkEffectUVPS2 base=uv[0],du,dv;
 du.u=uv[2].u-base.u;du.v=uv[2].v-base.v;dv.u=uv[1].u-base.u;dv.v=uv[1].v-base.v;
 determinant.f=edge2.z*edge1.y-edge2.y*edge1.z;
 scale=(determinant.u&0x7f800000)<=0x37800000?1.0f:1.0f/determinant.f;
 du.u*=scale;du.v*=scale;dv.u*=scale;dv.v*=scale;
 while(count>0) {
  BkEffectPointPS2 delta=BkEffectSpillPS2(BkEffectSubPS2(*points++,triangle[0]));
  f32 a=delta.z*edge1.y-delta.y*edge1.z,b=delta.y*edge2.z-delta.z*edge2.y;
  out->u=base.u+du.u*a+dv.u*b;out->v=base.v+du.v*a+dv.v*b;out++;count--;
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BAF90);
#endif

#ifdef NON_MATCHING
// Unmatched: sixteen-point fracture topology, wide vector return ABI and UV array alias lifetimes.
#include "game/effects/fracture.h"
extern s32 D_003F7470[4][2];
extern "C" void func_001BAB90(BkEffectUVPS2 *,const s128 *,const s128 *,const BkEffectUVPS2 *,int),func_001BAD90(BkEffectUVPS2 *,const s128 *,const s128 *,const BkEffectUVPS2 *,int),func_001BAF90(BkEffectUVPS2 *,const s128 *,const s128 *,const BkEffectUVPS2 *,int);
static inline f32 RadialLength(s128 v) {f32 sq=BkSumPS2(BkMultiplyPS2(v,v));extern f32 sqrtf(f32);return sqrtf(sq);}
static inline bool RadialEmit(BkEffectFracturePoolPS2 *pool,const s128 *points,const BkEffectUVPS2 *uv,int a,int b,int c,int d,s128 normal,s128 range,f32 scale,void *material,int pass,int flags,f32 lifetime,f32 multiplier) {
 BkEffectGeometryPS2 *geometry=BkEffectAllocateGeometryPS2(pool);if(!geometry)return false;
 int indices[4]={a,b,c,d},count=d<0?3:4;for(int i=0;i<count;i++){geometry->points[i]=points[indices[i]];geometry->uv[i]=uv[indices[i]];}
 s128 velocity=func_001BCA30(pool,range,scale);f32 spin=BkEffectRandomPS2()*multiplier;s128 direction=func_001BC880();func_001B9198(geometry,normal,velocity,count,0,material,(u8)pass,(u8)flags,direction,lifetime,spin);return true;
}
extern "C" void func_001BB190(BkEffectFracturePoolPS2 *pool,BkEffectGeometryPS2 *source,s128 point,s128 incoming,void *material,int pass,int flags,f32 scale) {
 if(pool->count>=254){func_001BC548(pool,point,incoming,0,0,0,0.3f,0.3f);return;}
 s128 normal=source->normal;if(BkSumPS2(BkMultiplyPS2(normal,incoming))>0)normal=BkEffectSubPS2(0,normal);
 s128 original[4]={source->points[0],source->points[1],source->points[3],source->points[2]};BkEffectUVPS2 originalUV[4]={source->uv[0],source->uv[1],source->uv[3],source->uv[2]};
 BkEffectPointPS2 sampledRange=BkEffectSpillPS2(BkEffectScalePS2(normal,scale/1.8f));sampledRange.x+=scale*0.3f;sampledRange.y+=scale*0.3f;sampledRange.z+=scale*0.3f;s128 points[20],range=*(s128 *)&sampledRange;
 BkEffectPointPS2 p=BkEffectSpillPS2(point);f32 lifetime=p.y-3-BkEffectRandomPS2()*12;scale*=2.5f;func_001BCA30(pool,range,scale);
 for(int i=0;i<4;i++) {
  points[16+i]=original[i];s128 edge=BkEffectSubPS2(original[i],point);f32 length=RadialLength(edge),minimum=length*0.1f,maximum=length*0.8f;if(minimum<0.1f)minimum=0.1f;if(maximum>0.5f)maximum=0.5f;
  points[i]=BkEffectAddPS2(point,BkEffectScalePS2(BkNormalizePS2(edge),minimum+BkEffectRandomPS2()*(maximum-minimum)));
  points[4+i]=BkEffectLerpPS2(points[i],original[i],BkEffectRandomPS2()*0.2f+0.4f);
  int a=D_003F7470[i][0],b=D_003F7470[i][1];points[8+i]=BkEffectLerpPS2(original[a],original[b],BkEffectRandomPS2()*0.2f+0.4f);
 }
 for(int i=0;i<4;i++){int a=D_003F7470[i][0],b=D_003F7470[i][1];points[12+i]=BkEffectLerpPS2(points[4+a],points[4+b],BkEffectRandomPS2()*0.2f+0.4f);}
 BkEffectUVPS2 uv[20];for(int i=0;i<4;i++)uv[16+i]=originalUV[i];BkEffectPointPS2 n=BkEffectSpillPS2(normal);f32 ax=n.x<0?-n.x:n.x,ay=n.y<0?-n.y:n.y;
 if(ax>=0.577f)func_001BAF90(uv,points,original,originalUV,16);else if(ay>=0.577f)func_001BAD90(uv,points,original,originalUV,16);else func_001BAB90(uv,points,original,originalUV,16);
 for(int i=0;i<4;i++) {
  int a=D_003F7470[i][0],b=D_003F7470[i][1];
  if(!(i&1)) {
   if(!RadialEmit(pool,points,uv,16+a,8+i,4+a,-1,normal,range,scale,material,pass,flags,lifetime,5))return;
   if(!RadialEmit(pool,points,uv,16+b,8+i,4+b,-1,normal,range,scale,material,pass,flags,lifetime,5))return;
   if(!RadialEmit(pool,points,uv,4+b,8+i,4+a,-1,normal,range,scale,material,pass,flags,lifetime,5))return;
  } else if(!RadialEmit(pool,points,uv,16+a,16+b,4+a,4+b,normal,range,scale,material,pass,flags,lifetime,5))return;
  if(!RadialEmit(pool,points,uv,4+a,12+i,a,-1,normal,range,scale,material,pass,flags,lifetime,10))return;
  if(!RadialEmit(pool,points,uv,4+b,12+i,b,-1,normal,range,scale,material,pass,flags,lifetime,10))return;
  if(!RadialEmit(pool,points,uv,a,12+i,b,-1,normal,range,scale,material,pass,flags,lifetime,10))return;
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BB190);
#endif

#ifdef NON_MATCHING
// Unmatched: VU operator load order and seven remaining allocation differences.
// Layouts are accessed prefixes, not assertions about the original class names.
#include "game/effects/vu_math.h"
namespace EffectCallbackProposal {
typedef s128 Value;
struct Matrix { Value row[4]; };
struct Pair { Value first,second; };
struct Actor {
    unsigned char unknown00[0x70];
    Matrix world;
    unsigned char unknownb0[0x14];
    int kind;
};
struct Hit {
    Value position;
    unsigned char unknown10[0x14];
    Actor* actor;
    unsigned char unknown28[4];
    unsigned char bone;
};
extern const Pair* BonePair(Actor*,unsigned char) __asm__("func_00148498");
extern const Matrix* BoneMatrix(Actor*,unsigned char) __asm__("func_00147988");
extern const Pair* DefaultPair(Actor*) __asm__("func_001528B8");
extern void* gRecipient __asm__("D_0040F4D4");
extern void Notify(void*,Value,void*) __asm__("func_0016E250");
class Callback {
public:
    void Emit(const Hit*,void*) __asm__("func_001BC428");
    // The two floats occupy F12/F13 independently of the four GPR arguments.
    void Spawn(Value,Value,int,float,float) __asm__("func_001BC548");
};
static inline Value Transform(const Matrix* m,Value direction)
{
    Value result;
    asm("vmulax.xyz ACC, matrixx, dirvx\n\t"
        "vmadday.xyz ACC, matrixy, dirvy\n\t"
        "vmaddaz.xyz ACC, matrixz, dirvz\n\t"
        "vmaddw.xyz answer, basevec, vf0w"
        : "=j answer"(result)
        : "j matrixy"(m->row[1]),"j matrixx"(m->row[0]),
          "j matrixz"(m->row[2]),"j basevec"(m->row[3]),"j dirv"(direction));
    return result;
}
void Callback::Emit(const Hit* hit,void* context)
{
    Actor* actor=hit->actor;
    if(actor && (unsigned)(actor->kind-3)<2) {
        Value position=hit->position;
        const Pair* pair;
        const Matrix* world;
        if(actor->kind==4) {
            pair=BonePair(actor,hit->bone);
            world=BoneMatrix(hit->actor,hit->bone);
        } else {
            pair=DefaultPair(actor);
            world=&hit->actor->world;
        }
        Value direction=BkEffectSubPS2(pair->first,pair->second);
        Value displaced=Transform(world,direction);
        displaced=BkEffectSubPS2(displaced,world->row[3]);
        Value scaled=BkEffectScalePS2(displaced,0.5f);
        Spawn(position,scaled,4,1.5f,1.0f);
        Notify(gRecipient,position,context);
    }
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BC428);
#endif

#ifdef NON_MATCHING
#include "game/effects/geometry.h"
#include "game/effects/random.h"
#include "game/actor/vector_math.h"
extern "C" { extern char *D_0040F4D8;void func_001B1728(s128,s128,BkEffectVectorPS2 *);void func_001B7A00(void *,void *,s64,int); }
static inline s128 Add(s128 a,s128 b) {s128 r;__asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;}
static inline s128 Scale(s128 a,f32 scale) {s128 r,s;__asm__("qmtc2.ni fr, sv":"=j sv"(s):"r fr"(scale));__asm__("vmulx.xyz outv, av, svx":"=j outv"(r):"j av"(a),"j sv"(s));return r;}
// Unmatched: orthogonal basis spills and interleaved random-state updates.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BC548);
#endif

#ifdef NON_MATCHING
// Unmatched: VU normalization and random-state scheduling.
#include "game/effects/random.h"
#include "game/actor/vector_math.h"
extern "C" s128 func_001BC880(void) {
 union {f32 f;u32 u;} x,y,z;
 s128 a,b,vector,result,square,sum,one=BkOnePS2();
 x.f=BkEffectRandomPS2()+0.01f;y.f=BkEffectRandomPS2();z.f=BkEffectRandomPS2();
 __asm__("pextlw outv, zv, xv":"=r outv"(a):"r zv"(z.u),"r xv"(x.u));
 __asm__("pextlw outv, yv, av":"=r outv"(b):"r yv"(y.u),"r av"(a));
 vector=b;
 square=BkMultiplyPS2(vector,vector);
 __asm__("vadday.x ACC, vv, vvy\n\tvmaddz.x sumv, onev, vvz":"=j sumv"(sum):"j vv"(square),"j onev"(one));
 __asm__("vnop\n\tvnop\n\tvnop\n\tvrsqrt Q, vf0w, sumvx\n\tvwaitq\n\tvmulq.xyz outv, vv, Q":"=j outv"(vector):"j vv"(vector),"j sumv"(sum));
 __asm__("qmfc2.ni outv, vv":"=r outv"(result):"j vv"(vector));return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BC880);
#endif

#ifdef NON_MATCHING
#include "game/effects/vector.h"
#include "game/effects/random.h"
// Unmatched: VU scalar lane extraction spills and random-state scheduling.
extern "C" s128 func_001BCA30(void *,s128 range,f32 scale) {
 BkEffectPointPS2 source= BkEffectSpillPS2(range),result;
 result.x=source.x*BkEffectRandomPS2()*scale;
 result.y=source.y*BkEffectRandomPS2()*scale;
 result.z=source.z*BkEffectRandomPS2()*scale;
 return *(s128 *)&result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BCA30);
#endif
