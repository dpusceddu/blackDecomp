#include "game/effects/slot.h"
#include "game/effects/inverse.h"
extern "C" void func_001B3A50(BkEffectSlotPS2 *,char *);
// Unmatched: inverse-basis lane extraction and matrix stack/register lifetimes.
#ifdef NONMATCHING
extern "C" BkEffectSlotPS2 *func_001B3420(BkEffectSlotPS2 *slots,char *attachment,s128 *matrix) {
 char *actor=*(char **)(attachment+0x24);BkEffectInverseLocalPS2((s128 *)(actor+0x70),matrix);
 u16 index=*(u16 *)(actor+0x1bc);if(index==0xffff) {func_001B3A50(slots,actor);index=*(u16 *)(actor+0x1bc);}
 return slots+index;
}
#endif // NONMATCHING
