#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0040DEE4;

void func_002A6C00(s32 arg0) {
    D_0040DEE4 = arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6C08);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002A6CC8);
