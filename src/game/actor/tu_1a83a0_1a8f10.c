#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001AAF10();
extern s8 * func_00137AE0();
extern s8 D_0040D9C8;

void func_001A8F10(s8 *arg0, s32 arg1, s8 *arg2) {
    func_001AAF10(arg0, arg1, arg2 + 0x3B9, func_00137AE0(arg2), "U_101", &D_0040D9C8, arg2);
}


INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1a83a0_1a8f10", func_001A9EA0);

