#include "game/effects/slot.h"
extern u16 func_001B3AE8(BkEffectSlotPS2 *,u16,u16,u16,u16,void *,u8);
void func_001B3A90(BkEffectSlotPS2 *slots,char *actor,u8 bone) {
 u16 index=func_001B3AE8(slots,20,28,0xc80,0x20,actor,bone);
 (*(u16 **)(actor+0x1b0))[bone]=index;
}
