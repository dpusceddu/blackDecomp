// Unmatched: VU axis rotation lanes, geometry copies and deferred-impact ABI lifetimes.
#ifdef NONMATCHING
#include "game/effects/vu_math.h"
struct BkEffectSimulationPS2 {
 int count;u8 padding[12];BkEffectGeometryPS2 records[255];
 BkEffectGeometryPS2 *pending[32];void *batches[32];f32 scale[32];s16 indices[32];f32 timeout[32];u8 kinds[32];
};
extern int D_004159D0;extern s128 D_004159C0;extern char *D_0040F4D0,*D_0040F4D8,*D_0040F510;
extern "C" void func_001B8138(void *),func_001B8180(void *,BkEffectGeometryPS2 *);
extern "C" void func_001BC548(void *,s128,s128,int,int,int,f32,f32),func_001DF080(s128 *);
extern "C" void func_001B8798(void *,BkEffectGeometryPS2 *,void *,int,int,f32);
extern "C" void func_001B1728(s128,s128,s128 *),func_001B7A00(void *,void *,s64,int),func_001EAAC8(void *,s128);
static inline f32 EffectLength(s128 v){s128 sq=BkMultiplyPS2(v,v),sum,one=BkOnePS2(),r;f32 x;__asm__("vadday.x ACC, sqv, sqvy\n\tvmaddz.x sumv, onev, sqvz":"=j sumv"(sum):"j sqv"(sq),"j onev"(one));__asm__("vnop\n\tvnop\n\tvnop\n\tvsqrt Q, sumvx\n\tvaddw.x outv, vf0, vf0w\n\tvwaitq\n\tvmulq.x outv, outv, Q":"=j outv"(r):"j sumv"(sum));__asm__("qmfc2.ni valuev, inv":"=r valuev"(x):"j inv"(r));return x;}
extern "C" void func_001B89C8(BkEffectSimulationPS2 *system) {
 if(!D_004159D0){BkEffectPointPS2 g={0,-0.01f,0,0};D_004159C0=*(s128 *)&g;D_004159D0=1;}
 void *buckets=(char *)system+0x11164;func_001B8138(buckets);
 for(int i=0;i<system->count;i++) {
  BkEffectGeometryPS2 *geometry=system->records+i;geometry->frames--;
  if((s16)geometry->frames<=0){--system->count;if(i!=system->count)*geometry=system->records[system->count];--i;continue;}
  if((s16)geometry->tag>0){geometry->tag--;func_001B8180(buckets,geometry);continue;}
  BkEffectPointPS2 position=BkEffectSpillPS2(geometry->transform[3]);
  if(position.y<=geometry->lifetime) {
   BkEffectPointPS2 velocity=BkEffectSpillPS2(geometry->velocity);
   if(velocity.y<0||geometry->elapsed>90) {
    f32 fragments=geometry->area*10.0f;geometry->frames=0;if(fragments<1)fragments=1;if(fragments>3)fragments=3;
    if(fragments>=1) {
     f32 length=EffectLength(BkEffectSubPS2(geometry->points[2],geometry->points[0]));BkEffectPointPS2 point=position;point.y+=length*0.2f;
     func_001BC548(system,*(s128 *)&point,geometry->normal,(int)fragments,0,0,length,length);s128 transform[4];func_001DF080(transform);
     func_001B8180(buckets,geometry);continue;
    }
   }
   union{f32 f;u32 u;} speed;speed.f=geometry->size;
   if((speed.u&0x7f800000)<=0x37800000){geometry->velocity=0;geometry->gravity=0;geometry->unknownFC=0.1f;geometry->size=0;}
  }
  f32 speed=geometry->size+geometry->unknownFC,angle=geometry->elapsed+speed;s128 rotation[4];BkEffectAxisRotationPS2(rotation,geometry->direction,angle*0.017453292f);
  s128 velocity=BkEffectAddPS2(geometry->velocity,geometry->gravity);for(int j=0;j<3;j++)geometry->transform[j]=rotation[j];
  geometry->transform[3]=BkEffectAddPS2(geometry->transform[3],velocity);geometry->velocity=velocity;geometry->size=speed;geometry->elapsed=angle;func_001B8180(buckets,geometry);
 }
 for(int i=0;i<32;i++)if(system->pending[i]) {
  system->timeout[i]-=*(f32 *)(D_0040F4D0+0x1c);if(system->timeout[i]<=0) {
   BkEffectGeometryPS2 *geometry=system->pending[i];func_001B8798(system,geometry,system->batches[i],system->indices[i],system->kinds[i],system->scale[i]);
   s128 midpoint=BkEffectAddPS2(geometry->points[0],BkEffectScalePS2(BkEffectSubPS2(geometry->points[2],geometry->points[0]),0.5f));s128 transform[4];func_001B1728(midpoint,geometry->normal,transform);
   func_001B7A00(D_0040F4D8+0x696f0,transform,(s64)0x6855dd9f6b702000ULL,1);void *sound=*(void **)(*(char **)(D_0040F510+0xcbd8)+0x28);func_001EAAC8(sound,transform[3]);system->pending[i]=0;
  }
 }
}
#endif // NONMATCHING
