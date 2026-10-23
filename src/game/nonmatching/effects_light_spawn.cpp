// Unmatched: three VU axis rotations, random-state ordering and stack matrix lifetimes.
#ifdef NONMATCHING
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
#endif // NONMATCHING
