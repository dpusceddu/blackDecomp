#include "include_asm.h"
#include "ps2/prelude.h"
#include "game/weapons/inventory.h"

u16 func_00155198(BkInventoryPS2 *arg0) {
    return BkInventorySlotPS2(arg0,7);
}

void func_001551A0(BkInventoryPS2 *arg0, s16 arg1) {
    arg0->reserve[7] = arg1;
}
