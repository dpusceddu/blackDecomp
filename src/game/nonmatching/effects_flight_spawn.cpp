// Unmatched: VU R-register lane order, mixed integer/float ranges and constructor stack lifetimes.
#ifdef NONMATCHING
#include "game/effects/vu_math.h"
#include "game/effects/random.h"
#include "game/effects/flight.h"
struct BkFlightConfigPS2 {u32 unknown[2];s64 id;u32 unknown10,unknown14;f32 lifetime;u16 count,pad;u32 unknown20;f32 minSpeed,maxSpeed,minSpin,maxSpin;s32 minAngle,maxAngle,minPitch,maxPitch;u8 relative;};
struct BkFlightAssetPS2 {s64 id;void *asset;u32 padding;};
struct BkFlightAssetsPS2 {u32 unknown[2];s32 count;BkFlightAssetPS2 *entries;};
extern char *D_0040F4D0,*D_0040F4D8;extern s128 D_00415B40,D_00415B50,D_00415B80[2];
extern "C" int func_001B1168(BkEffectEntryPS2 *,s128 *,void *,int,f32);
extern "C" int func_001BEF70(BkEffectFlightPS2 *flights,s128 point,BkFlightConfigPS2 *config) {
 f32 now=*(f32 *)(D_0040F4D0+0x20),dt=*(f32 *)(D_0040F4D0+0x1c);BkEffectVUSeedPS2(BkEffectRandomPS2());
 BkEffectPointPS2 high={(f32)config->minPitch*0.017453292f,config->minSpin*dt,(f32)config->minAngle*0.017453292f,config->minSpeed},low={(f32)config->maxPitch*0.017453292f,config->maxSpin*dt,(f32)config->maxAngle*0.017453292f,config->maxSpeed};
 BkEffectPointPS2 range={low.x-high.x,low.y-high.y,low.z-high.z,low.w-high.w};s128 delta=*(s128 *)&range;void *asset=0;
 BkFlightAssetsPS2 *assets=*(BkFlightAssetsPS2 **)(*(char **)(D_0040F4D8+0x873f0)+8);
 for(int i=0;i<assets->count;i++)if(assets->entries[i].id==config->id){asset=assets->entries[i].asset;break;}
 u16 remaining=config->count;int result=0;
 for(u16 i=0;i<44;i++) {
  BkEffectFlightPS2 *flight=flights+i;if(flight->active)continue;remaining--;flight->active=1;flight->relative=config->relative;
  s128 random=BkEffectVUNextXPS2();
  if(config->relative){random=BkEffectVUNextYZPS2(random);s128 scale=D_00415B40,unit=BkEffectVUUnitRandomPS2(random,scale,D_00415B50);D_00415B40=BkEffectVURotateLanesPS2(scale);flight->localOffset=BkEffectAddPS2(D_00415B80[0],BkMultiplyPS2(D_00415B80[1],unit));}
  flight->origin=BkEffectSpillPS2(point);flight->origin.w=now;flight->lifetime=config->lifetime;
  random=BkEffectVUNextPS2();s128 scale=D_00415B40,unit=BkEffectVUUnitRandomPS2(random,scale,D_00415B50);scale=BkEffectVURotateLanesPS2(scale);
  BkEffectPointPS2 rv=BkEffectSpillPS2(unit),d=BkEffectSpillPS2(delta),sample={high.x+d.x*rv.x,high.y+d.y*rv.y,high.z+d.z*rv.z,high.w+d.w*rv.w};
  random=BkEffectVUNextYZPS2(random);unit=BkEffectVUUnitRandomPS2(random,scale,D_00415B50);D_00415B40=BkEffectVURotateLanesPS2(scale);
  s128 axis=BkNormalizePS2(BkEffectAddPS2(D_00415B80[0],BkMultiplyPS2(D_00415B80[1],unit)));
  BkEffectAxisRotationPS2(flight->initial,axis,sample.y*0.017453292f);
  s128 trig=BkEffectVUSinCosPS2(sample.x,sample.z);BkEffectPointPS2 sc=BkEffectSpillPS2(trig);BkEffectPointPS2 velocity={sc.z*sc.y,sc.x,sc.w*sc.w,0};
  flight->velocity=BkEffectSpillPS2(BkEffectScalePS2(*(s128 *)&velocity,sample.w));
  BkEffectPointPS2 identity[4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,0}};for(int j=0;j<4;j++)flight->world[j]=*(s128 *)&identity[j];
  u32 *state=(u32 *)&flight->child;for(int j=0;j<8;j++)state[j]=0;*(u32 *)((char *)flight+0x110)=0;
  result=func_001B1168(&flight->child,flight->world,asset,1,now);if(remaining==0)return result;
 }
 return result;
}
#endif // NONMATCHING
