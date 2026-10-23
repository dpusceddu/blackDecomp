// Unmatched: slot object-field base hoisting; five-word near miss.
#ifdef NONMATCHING
#include "game/effects/slot.h"
extern u16 func_001B3BD0(BkEffectSlotPS2 *,u16,u16);
extern int func_001B3CF8(BkEffectSlotPS2 *,BkEffectSlottedObjectPS2 *,u16,u16,u8);
u16 func_001B3AE8(BkEffectSlotPS2 *slots,u16 first,u16 limit,u16 offset,u16 stride,void *object,u8 mode) {
 u16 index=first; for(;index<limit;index++)if(!slots[index].object)break;
 if(index==limit)index=func_001B3BD0(slots,first,index);
 func_001B3CF8(slots+index,object,(u16)((index-first)*stride+offset),stride,mode);return index;
}

#endif // NONMATCHING
