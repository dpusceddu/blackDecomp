#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003D24C4;

void func_00347948(s32 arg0) {
    D_003D24C4 = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/animation/tu_347948", func_00347958);
