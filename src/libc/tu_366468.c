#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00366468();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366468);

void func_00366510(void *arg0, void *arg1) {
    s32 temp_4;

    if (arg1 != NULL) {
        temp_4 = M2C_FIELD(arg1, s32 *, 4) * 4;
        M2C_FIELD(arg1, s32 *, 0) = (s32) M2C_FIELD((temp_4 + M2C_FIELD(arg0, s32 *, 0x4C)), s32 *, 0);
        M2C_FIELD((temp_4 + M2C_FIELD(arg0, s32 *, 0x4C)), u32 *, 0) = arg1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366788);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366810);

s32 func_003668D0(s32 arg0, s32 arg1) {
    void *temp_2;

    temp_2 = func_00366468(arg0, 1);
    M2C_FIELD(temp_2, s32 *, 0x14) = arg1;
    M2C_FIELD(temp_2, s32 *, 0x10) = 1;
    return (s32) temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366B10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366C10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366D68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366DD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00366F60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00367028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003671C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00367340);
