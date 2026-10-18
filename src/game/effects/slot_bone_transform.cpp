#include "game/effects/slot.h"
#include "game/effects/inverse.h"
extern "C" {char *func_001AFD80(void *,void *);s128 *func_00147988(void *,u8);void func_001B3A90(BkEffectSlotPS2 *,char *,u8);}
// Unmatched: inverse-bone transpose lane extraction and matrix temporary lifetimes.
#ifdef NONMATCHING
extern "C" BkEffectSlotPS2 *func_001B3590(BkEffectSlotPS2 *slots,char *attachment,s128 *matrix) {
 char *actor=*(char **)(attachment+0x24);u8 bone=*(u8 *)(attachment+0x2c);
 if(bone<*(u8 *)(actor+0x1f6)) {
  char *asset=func_001AFD80(*(char **)(actor+0x1a0)+bone*0xc,*(void **)(actor+0x118));
  if(!asset||*(int *)(asset+0x54)!=3) {
   s128 *world=func_00147988(actor,bone);BkEffectInverseLocalPS2(world,matrix);
   u16 *indices=*(u16 **)(actor+0x1b0);if((s16)indices[bone]==-1) {func_001B3A90(slots,actor,bone);indices=*(u16 **)(actor+0x1b0);}
   return slots+indices[bone];
  }
 }
 return 0;
}
#endif // NONMATCHING
