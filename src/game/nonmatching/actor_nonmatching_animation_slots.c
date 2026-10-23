// Unmatched: 0x1ac798: slot pointer register allocation and call scheduling.
#ifdef NONMATCHING
#include "auto/prelude.h"
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

#endif
