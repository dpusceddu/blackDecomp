// Unmatched: twenty-fragment UV workspace, table-owned tags and scalar/VU temporary lifetimes.
#ifdef NONMATCHING
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
#endif // NONMATCHING
