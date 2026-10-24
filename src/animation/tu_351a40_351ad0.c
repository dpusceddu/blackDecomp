#include "include_asm.h"
#include "ps2/prelude.h"

void func_00351AD0(s32 *arg0) {
    *arg0 -= 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00351AE0);

s32 func_00351B38(s32 *arg0) {
    return *arg0 > 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00351B48);
