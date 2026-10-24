#include "include_asm.h"
#include "ps2/prelude.h"

void func_00281F88(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xD) = 0;
    M2C_FIELD(arg0, s64 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s8 *, 0xC) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00281FA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00282008);
