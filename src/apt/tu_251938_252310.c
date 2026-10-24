#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003BFAE0;

void func_00252310(s32 arg0, s32 *arg1) {
    *arg1 = D_003BFAE0;
    D_003BFAE0 = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252328);
