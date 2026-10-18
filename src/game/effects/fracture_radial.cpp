// Unmatched: sixteen-point fracture topology, wide vector return ABI and UV array alias lifetimes.
#ifdef NONMATCHING
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
#endif // NONMATCHING
