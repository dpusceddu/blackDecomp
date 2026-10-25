#include "include_asm.h"

#include "game/effects/slot.h"
extern u16 func_001B3AE8(BkEffectSlotPS2 *,u16,u16,u16,u16,void *,u8);

void func_001B3A90(BkEffectSlotPS2 *slots,char *actor,u8 bone) {
 u16 index=func_001B3AE8(slots,20,28,0xc80,0x20,actor,bone);
 (*(u16 **)(actor+0x1b0))[bone]=index;
}

#ifdef NON_MATCHING
// Unmatched: slot object-field base hoisting; five-word near miss.
#include "game/effects/slot.h"
extern u16 func_001B3BD0(BkEffectSlotPS2 *,u16,u16);
extern int func_001B3CF8(BkEffectSlotPS2 *,BkEffectSlottedObjectPS2 *,u16,u16,u8);
u16 func_001B3AE8(BkEffectSlotPS2 *slots,u16 first,u16 limit,u16 offset,u16 stride,void *object,u8 mode) {
 u16 index=first; for(;index<limit;index++)if(!slots[index].object)break;
 if(index==limit)index=func_001B3BD0(slots,first,index);
 func_001B3CF8(slots+index,object,(u16)((index-first)*stride+offset),stride,mode);return index;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/slot_bone", func_001B3AE8);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/effects/slot_bone", func_001B3BD0);
