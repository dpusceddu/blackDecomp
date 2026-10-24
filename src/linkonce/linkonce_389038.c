#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_004433C0;

s32 func_00389038(void) {
    return 0;
}

M2C_UNK * func_00389040(void) {
    return &D_004433C0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00389050);
