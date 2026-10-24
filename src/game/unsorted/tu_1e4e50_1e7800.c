#include "include_asm.h"
#include "ps2/prelude.h"

void func_001E7800(void *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E7810);
