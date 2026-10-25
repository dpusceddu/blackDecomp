#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/effects/flight.h"
#include "game/effects/geometry.h"
extern "C" {extern char *D_0040F4D0,*D_0040F4D8;void func_001B15A0(BkEffectEntryPS2 *),func_001B1518(BkEffectEntryPS2 *),func_001B11A0(BkEffectEntryPS2 *);int func_001B1340(BkEffectEntryPS2 *,void *,f32,f32);}
// Unmatched: flight vector y/w lanes and matrix multiplication temporary lifetimes.
extern "C" void func_001BECD0(BkEffectFlightPS2 *flights) {
 f32 now=*(f32 *)(D_0040F4D0+0x20),elapsedFrame=now-*(f32 *)(D_0040F4D0+0x1c);
 for(u16 index=0;index<44;index++) {
  BkEffectFlightPS2 *flight=flights+index;
  if(flight->active) {
   f32 elapsed=now-flight->origin.w;
   if(flight->lifetime<elapsed) {flight->active=0;if(flight->child.resource) {func_001B15A0(&flight->child);func_001B1518(&flight->child);}}
   else if(!flight->child.resource)flight->active=0;
   else {
    BkEffectPointPS2 position={flight->origin.x+flight->velocity.x*elapsed,flight->origin.y+flight->velocity.y*elapsed+0.5f*flight->velocity.w*elapsed*elapsed,flight->origin.z+flight->velocity.z*elapsed,0};
    flight->world[3]=*(s128 *)&position;
    if(flight->relative) {
     s128 combined[4];flight->world[3]=BkEffectTransformPS2(flight->world,flight->localOffset);
     for(int i=0;i<3;i++)combined[i]=BkEffectRotatePS2(flight->world,flight->initial[i]);combined[3]=BkEffectTransformPS2(flight->world,flight->initial[3]);
     for(int i=0;i<4;i++)flight->world[i]=combined[i];
    }
    func_001B11A0(&flight->child);if(!func_001B1340(&flight->child,D_0040F4D8,now,elapsedFrame))func_001B1518(&flight->child);
   }
  }
 }
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BECD0);
#endif

#ifdef NON_MATCHING
// Unmatched: 0x1bef70: 44 flight slots, true 64-bit IDs, VU I/ACC trig orientation and 128-bit particle state.
// Unmatched: 0x1bf918: signed rounding and packed count clamp, emitter fraction and mixed-width spawn callback ABI.
// Unmatched: 0x1c0a78: signed fractional light counts, VU I/ACC random basis and vector-valued spawn arguments.
#endif

#ifdef NON_MATCHING
// Unmatched: VU R-register lane order, mixed integer/float ranges and constructor stack lifetimes.
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
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BEF70);
#endif


#ifdef NON_MATCHING
#include "game/effects/vector.h"
extern "C" {extern char *D_0040F4D0;extern s128 D_00415A70,D_00415A90;extern int D_00415A80,D_00415AA0;void func_001B1038(...);int func_0012AE58(void *,s128,s128,int,int,int,void *);}
static inline s128 Add(s128 a,s128 b) {s128 r;__asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;}
static inline s128 Half(s128 a) {s128 r,s;__asm__("qmtc2.ni fr, sv":"=j sv"(s):"r fr"(0.5f));__asm__("vmulx.xyz outv, av, svx":"=j outv"(r):"j av"(a),"j sv"(s));return r;}
// Unmatched: ground-ray hit aggregate, vector argument bank and static vector initialization.
extern "C" int func_001C0910(char *light,void *owner,void *resource,void *context,const s128 *transform) {
 BkEffectPointPS2 up={0,0.2f,0,0},down={0,-100,0,0},hit[4];
 if(!D_00415A80) {D_00415A70=*(s128 *)&up;D_00415A80=1;}
 if(!D_00415AA0) {D_00415A90=*(s128 *)&down;D_00415AA0=1;}
 func_001B1038(light,owner,resource);*(u32 *)(light+0x54)=0;
 s128 half=Half(transform[2]),bottom=Add(Add(transform[3],D_00415A90),half),top=Add(Add(transform[3],D_00415A70),half);
 if(func_0012AE58(D_0040F4D0,top,bottom,1,0,1,hit))*(f32 *)(light+0x58)=hit[0].y;
 else *(f32 *)(light+0x58)=BkEffectSpillPS2(transform[3]).y-3.0f;
 *(void **)(light+0x50)=context;return 1;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C0910);
#endif

#ifdef NON_MATCHING
// Unmatched: three VU axis rotations, random-state ordering and stack matrix lifetimes.
#include "game/effects/vu_math.h"
#include "game/effects/random.h"
struct BkLightConfigPS2 {u32 type;f32 frequency,lifetime,minSpeed,maxSpeed;u32 unknown14,unknown18;f32 minSpread,maxSpread,offset;};
struct BkLightOwnerPS2 {f32 duration;u32 unknown;};
struct BkLightEmissionPS2 {s128 transform[4];BkLightConfigPS2 *config;u32 unknown44;f32 birth,last;BkLightOwnerPS2 *owner;f32 fraction,ground;u32 unknown5c;};
extern "C" int func_001B1070(void *,f32);
extern "C" void func_001D1B40(BkLightOwnerPS2 *,s128,s128,f32,f32);
extern "C" int func_001C0A78(BkLightEmissionPS2 *record,f32 now) {
 BkLightConfigPS2 *config=record->config;f32 end=record->birth+config->lifetime;if(now>end+record->owner->duration)return 0;
 f32 elapsed=now-record->last;if(now>end){elapsed=end-record->last;if(elapsed<0)elapsed=0;}
 f32 fractional=elapsed*config->frequency+record->fraction;union {f32 f;u32 u;} half,bits;bits.f=fractional;half.u=(bits.u&0x80000000)|0x3f000000;
 int count=(int)(fractional+half.f);if(count<0)count=0;record->fraction=fractional-(f32)count;
 while(count-->0) {
  f32 spread=(config->minSpread+(config->maxSpread-config->minSpread)*BkEffectRandomPS2())*57.29578f*0.017453292f;
  s128 first[4],second[4],third[4];BkEffectAxisRotationPS2(first,record->transform[0],spread);
  s128 cone=BkEffectRotatePS2(first,record->transform[2]);f32 azimuth=BkEffectRandomPS2()*6.2831855f;
  BkEffectAxisRotationPS2(second,record->transform[2],azimuth*57.29578f*0.017453292f);
  s128 direction=BkEffectRotatePS2(second,cone);
  f32 speed=config->minSpeed+(config->maxSpeed-config->minSpeed)*BkEffectRandomPS2();direction=BkEffectScalePS2(direction,speed);
  BkEffectAxisRotationPS2(third,record->transform[2],azimuth*57.29578f*0.017453292f);
  s128 offset=BkEffectScalePS2(BkEffectSubPS2(0,record->transform[1]),config->offset),position=BkEffectAddPS2(BkEffectRotatePS2(third,offset),record->transform[3]);
  func_001D1B40(record->owner,position,direction,now-BkEffectRandomPS2()*elapsed,record->ground);
 }
 return func_001B1070(record,now);
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C0A78);
#endif
