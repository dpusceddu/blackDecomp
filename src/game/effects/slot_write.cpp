#include "game/effects/slot.h"
#include "game/effects/geometry.h"
#include "game/effects/random.h"
#include "game/actor/vector_math.h"
extern "C" {extern char *D_0040F4D0;BkEffectSlotPS2 *func_001B33B8(BkEffectSlotPS2 *,const s128 *);BkEffectSlotPS2 *func_001B3420(BkEffectSlotPS2 *,void *,s128 *),*func_001B3590(BkEffectSlotPS2 *,void *,s128 *);int func_0012C790(void *,s128);void func_001AEBF8(int,void *,s128 *,s128 *,s128 *,int);}
struct BkEffectSlotHitPS2 {s128 point,normal;u32 unknown;char *attachment;};
struct BkEffectSlotVertexPS2 {BkEffectPointPS2 position;BkEffectPointPS2 normal;};
static inline s128 Add(s128 a,s128 b) {s128 r;__asm__("vadd.xyz outv, av, bv":"=j outv"(r):"j av"(a),"j bv"(b));return r;}
static inline s128 Scale(s128 a,f32 scale) {s128 r,s;__asm__("qmtc2.ni fr, sv":"=j sv"(s):"r fr"(scale));__asm__("vmulx.xyz outv, av, svx":"=j outv"(r):"j av"(a),"j sv"(s));return r;}
// Unmatched: spherical-lighting component masks and vector/packed-ring register lifetimes.
#ifdef NONMATCHING
extern "C" void func_001B2E08(BkEffectSlotPS2 *slots,BkEffectSlotHitPS2 *hit,u8 kind,f32 minimum,f32 maximum) {
 BkEffectPointPS2 identity[4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,0}};s128 transform[4];for(int i=0;i<4;i++)transform[i]=*(s128 *)&identity[i];
 BkEffectSlotPS2 *slot=0;
 if(!hit->attachment)slot=func_001B33B8(slots,&hit->point);
 else {int category=*(int *)(hit->attachment+0xc4);if(category==3)slot=func_001B3420(slots,hit,transform);else if(category==4)slot=func_001B3590(slots,hit,transform);}
 if(!slot)return;
 s128 normal=hit->normal,point=hit->point;s128 query=Add(point,Scale(normal,0.2f));f32 brightness=0.4f;
 if(func_0012C790(D_0040F4D0,query)) {
  s128 coeff[3];u8 flags[3];func_001AEBF8(0,flags,&coeff[0],&coeff[1],&coeff[2],0);
  BkEffectPointPS2 a=BkEffectSpillPS2(coeff[0]),b=BkEffectSpillPS2(coeff[1]),c=BkEffectSpillPS2(coeff[2]),n=BkEffectSpillPS2(normal);
  brightness=b.z+c.z*n.z+n.x*(c.x+b.x*n.z+a.z*n.y+a.x*n.x)+n.y*(c.y+b.y*n.z+a.y*n.y);
  brightness=__ee_min_s(__ee_max_s(brightness,0.0f),1.0f);
 }
 point=Add(point,Scale(normal,0.02f));normal=BkEffectRotatePS2(transform,normal);point=BkEffectTransformPS2(transform,point);
 u16 index=slot->start+slot->write;BkEffectSlotVertexPS2 *vertices=(BkEffectSlotVertexPS2 *)((char *)slots+0x1c0);
 vertices[index].position=BkEffectSpillPS2(point);vertices[index].position.w=(minimum+(maximum-minimum)*BkEffectRandomPS2())*0.05f;
 u32 random=(u32)(BkEffectRandomPS2()*4294967296.0f)&3;BkEffectPointPS2 direction=BkEffectSpillPS2(normal);
 if(direction.y < -0.99f||direction.y>0.99f) {direction.z+=direction.z>0?0.01f:-0.01f;normal=BkNormalizePS2(*(s128 *)&direction);}
 vertices[index].normal=BkEffectSpillPS2(normal);u32 intensity=(u32)(brightness*127.95f),packed=(kind*4+random)|(intensity<<8)|(intensity<<16)|(intensity<<24);*(u32 *)&vertices[index].normal.w=packed;
 slot->used=slot->used+1<slot->count?slot->used+1:slot->count;slot->write=(slot->write+1)%slot->count;
}
#endif // NONMATCHING
