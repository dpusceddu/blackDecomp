// Unmatched: VU random/trig scheduling, partial lane writes and particle packet lifetimes.
#ifdef NONMATCHING
#include "game/effects/vu_math.h"
#include "game/effects/emitter.h"
#include "game/effects/random.h"
struct BkParticleConfigPS2 {u32 type;f32 frequency,lifetime,minSpeed,maxSpeed,minScale,maxScale,minEmission,maxEmission,drag,width,fade;};
struct BkParticleBatchPS2 {BkParticleBatchPS2 *next;f32 birth;int count;};
struct BkParticleOwnerPS2 {void *definition;BkParticleBatchPS2 *head;};
extern s128 D_00415B40,D_00415B50;
extern "C" int func_001B1070(void *,f32);
extern "C" void func_001C0840(void *,BkParticleBatchPS2 *);
extern "C" void func_001CFE50(BkParticleBatchPS2 *,s128,s128,f32,f32);
extern "C" int func_001BF918(BkEffectEmitterRecordPS2 *record,BkParticleBatchPS2 **freeList,f32 now) {
 s128 origin=record->transform[3],movement=BkEffectSubPS2(origin,record->ranges[4]);record->ranges[4]=origin;
 BkParticleConfigPS2 *config=(BkParticleConfigPS2 *)record->resource;now+=record->rate;
 f32 previous=record->lastUpdate,end=record->birthTime+config->lifetime,elapsed=now-previous;
 if(end<now){elapsed=end-previous;if(elapsed<0)elapsed=0;}
 f32 fade=1;if(config->fade<0.99f){fade=(end-now)/(config->lifetime*(1-config->fade));if(fade>=1)fade=1;}
 f32 fractional=elapsed*config->frequency+*(f32 *)&record->flags;union {f32 f;u32 u;} half,bits;bits.f=fractional;half.u=(bits.u&0x80000000)|0x3f000000;
 int count=(int)(fractional+half.f);if(count<0)count=0;*(f32 *)&record->flags=fractional-(f32)count;
 if(fade>0.001f&&count>0) {
  BkEffectVUSeedPS2(BkEffectRandomPS2());BkParticleOwnerPS2 *owner=(BkParticleOwnerPS2 *)record->owner;BkParticleBatchPS2 *batch=owner->head;
  BkEffectPointPS2 birth={0,0,0,previous},step={0,0,0,elapsed/(f32)count},zero={0,0,0,0},dragStep={0,0,0,elapsed*config->drag};
  s128 time=*(s128 *)&birth;
  do {
   if(!batch||batch->count==60) {batch=*freeList;if(!batch)return 1;*freeList=batch->next;func_001C0840(owner,batch);}
   int batchCount=60-batch->count;if(batchCount>count)batchCount=count;count-=batchCount;
   s128 randomA=BkEffectVUNextXPS2(),randomB=BkEffectVUNextXPS2();
   do {
    s128 random=BkEffectVUNextYZWPS2(randomA),scale=D_00415B40;
    s128 unit=BkEffectVUUnitRandomPS2(random,scale,D_00415B50);D_00415B40=BkEffectVURotateLanesPS2(scale);
    BkEffectPointPS2 low=BkEffectSpillPS2(record->ranges[0]),range=BkEffectSpillPS2(record->ranges[1]),u=BkEffectSpillPS2(unit);
    BkEffectPointPS2 sample={low.x+range.x*u.x,low.y+range.y*u.y,low.z+range.z*u.z,low.w+range.w*u.w};
    BkEffectPointPS2 trig=BkEffectSpillPS2(BkEffectVUSinCosPS2(sample.x,sample.z));
    s128 direction=BkEffectSubPS2(BkEffectAddPS2(BkEffectScalePS2(record->transform[2],trig.y),BkEffectScalePS2(record->transform[0],trig.x*trig.z)),BkEffectScalePS2(record->transform[1],trig.x*trig.w));
    direction=BkEffectScalePS2(direction,sample.y);
    scale=D_00415B40; s128 r=BkEffectVUUnitRandomPS2(randomB,scale,D_00415B50);D_00415B40=BkEffectVURotateLanesPS2(scale);
    BkEffectPointPS2 top=BkEffectSpillPS2(record->ranges[2]),delta=BkEffectSpillPS2(record->ranges[3]),rv=BkEffectSpillPS2(r),dir=BkEffectSpillPS2(direction);
    f32 size=top.x+delta.x*rv.x;if(sample.w<0)size=-size;dir.w=size;
    BkEffectPointPS2 t=BkEffectSpillPS2(time);t.z+=zero.z*trig.z-dragStep.z*trig.w;t.w+=zero.w*trig.z-dragStep.w*trig.w;
    func_001CFE50(batch,*(s128 *)&t,*(s128 *)&dir,top.y+delta.y*rv.x,fade);
    __asm__("vadd.xyzw outv, av, bv":"=j outv"(time):"j av"(time),"j bv"(*(s128 *)&step));
   }while(--batchCount);
   batch=0;
  }while(count);
 }
 return func_001B1070(record,now);
}
#endif // NONMATCHING
