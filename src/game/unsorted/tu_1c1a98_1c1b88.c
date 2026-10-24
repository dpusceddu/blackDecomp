#include "include_asm.h"
#include "ps2/prelude.h"

extern f32 D_003BD1CC;

s32 func_001C1B88(void) {
    D_003BD1CC = 1.0f;
    return 1;
}

s32 func_001C1BA0(void) {
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1BA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C1BB8);
