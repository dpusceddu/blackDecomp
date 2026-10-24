#include "include_asm.h"
#include "ps2/prelude.h"

void func_00312A10(void *arg0) {
    s32 temp_2;

    temp_2 = arg0 + 4;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = temp_2;
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
}

void func_00312A28(void *arg0) {
    s32 temp_2;

    temp_2 = arg0 + 4;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    M2C_FIELD(arg0, s32 *, 8) = temp_2;
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00312A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00312A80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00312AD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00312B40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00312B78);
