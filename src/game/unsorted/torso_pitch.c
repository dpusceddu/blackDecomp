#include "include_asm.h"

#include "ps2/prelude.h"
typedef struct { char padding[0x2e0]; float speed; } BkActorRatePS2;
extern BkActorRatePS2 **func_001AC040(void *);
extern void *func_00135550(BkActorRatePS2 *);
extern float func_0013EE68(void *), D_003BD18C;

float func_001AC4B8(void *context) {
 BkActorRatePS2 **actor=func_001AC040(context); float pitch=0.0f;
 if(func_00135550(*actor)) {
  float angle=func_0013EE68(func_00135550(*actor));
  pitch=angle;
  if((*actor)->speed>1.0f) pitch+=D_003BD18C;
  pitch*=1.3f;
  __asm__("max.s %0, %0, %1" : "+f" (pitch) : "f" (-90.0f));
  __asm__("min.s %0, %0, %1" : "+f" (pitch) : "f" (90.0f));
 }
 return -pitch;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AC568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AC5B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AC638);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AC648);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AC680);

#ifdef NON_MATCHING
// Unmatched: 0x1ac798: slot pointer register allocation and call scheduling.
#include "ps2/prelude.h"
typedef struct BkAnimationSlotPS2 { char pad[0xb0]; int index; } BkAnimationSlotPS2;
typedef struct BkActorAnimationPS2 { char pad[0x8f0]; char pool[0x4c]; BkAnimationSlotPS2 **slots; } BkActorAnimationPS2;
extern int func_001AE0A8(void *, int);
extern void func_001AC680(BkActorAnimationPS2 *, BkAnimationSlotPS2 *);
extern void func_001AE088(void *, int), func_001AE090(void *, int);
extern char *func_001ADFC0(void *, int);
extern void func_00343FC8(void *);
char *func_001AC798(BkActorAnimationPS2 *actor, BkAnimationSlotPS2 *slot) {
 char *result=0; int i=0; char *state; char *joint; int count; BkAnimationSlotPS2 **entry;
 for (;;) {
  if(i>=8) break;
  entry=(BkAnimationSlotPS2 **)(i++ * 4 + (unsigned int)actor->slots);
  if(*entry) continue;
  *entry=slot; slot->index=func_001AE0A8(actor->pool,i); break;
 }
 if(slot->index==-1) {
  func_001AC680(actor,slot); i=0;
  for (;;) {
   if(i>=8) break;
   entry=(BkAnimationSlotPS2 **)(i++ * 4 + (unsigned int)actor->slots);
   if(*entry) continue;
   *entry=slot; slot->index=func_001AE0A8(actor->pool,i); break;
  }
 }
 if(slot->index!=-1) {
  count=11; func_001AE088(actor->pool,0); func_001AE090(actor->pool,slot->index);
  state=func_001ADFC0(actor->pool,0x9d0); joint=state+0x1d0;
  func_00343FC8(state+0x30);
  do { --count; func_00343FC8(joint+0x10); func_00343FC8(joint+0x60); joint+=0xa0; } while(count!=-1);
  result=state;
 }
 return result;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AC798);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001AC8D0);
