#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00294260(void *, s32, s32, s32);

s32 func_00294AC8(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_5;
    void *temp_7;

    temp_7 = M2C_FIELD(arg0, void **, 0x40);
    temp_5 = (arg1 & 0x0FFFFFFF) | 0x20000000;
    M2C_FIELD(temp_7, s32 *, 0xC4) = 1;
    M2C_FIELD(temp_7, s32 *, 0xEC) = temp_5;
    M2C_FIELD(temp_7, s32 *, 0xF8) = arg2;
    M2C_FIELD(temp_7, s32 *, 0xF0) = 0;
    M2C_FIELD(temp_7, s32 *, 0xF4) = 0;
    return func_00294260(arg0, temp_5, arg2, (s32) temp_7);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294ac8", func_00294B10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294ac8", func_00294B18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294ac8", func_00294BA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294ac8", func_00294BB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294ac8", func_00294BE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294ac8", func_00294BF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_293e90_294ac8", func_00294C70);
