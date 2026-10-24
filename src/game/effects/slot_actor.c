#include "include_asm.h"

#include "game/effects/slot.h"
extern u16 func_001B3AE8(BkEffectSlotPS2 *,u16,u16,u16,u16,void *,u8);

void func_001B3A50(BkEffectSlotPS2 *slots,char *actor) {
 *(u16 *)(actor+0x1bc)=func_001B3AE8(slots,8,20,0x800,0x60,actor,0xff);
}
