#include "include_asm.h"
#include "ps2/prelude.h"

void func_003477F0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s16 temp_4;

    temp_4 = M2C_FIELD(arg0, s16 *, 0x5C);
    if (temp_4 < 9) {
        M2C_FIELD(((temp_4 * 0xC) + M2C_FIELD(arg0, s32 *, 0x58)), s32 *, 0) = arg1;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 0x5C) * 0xC) + M2C_FIELD(arg0, s32 *, 0x58)), s32 *, 4) = arg2;
        M2C_FIELD(((M2C_FIELD(arg0, s16 *, 0x5C) * 0xC) + M2C_FIELD(arg0, s32 *, 0x58)), s32 *, 8) = arg3;
        M2C_FIELD(arg0, s16 *, 0x5C) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0x5C) + 1);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00347858);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003478F0);
