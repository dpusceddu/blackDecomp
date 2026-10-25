#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00107D20();
extern s32 func_001ADDF8();

void func_001ADD78(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_17;
    s32 temp_2;

    temp_17 = arg3 * 4;
    M2C_FIELD(arg0, s32 *, 0) = func_00107D20(temp_17);
    temp_2 = func_00107D20(temp_17);
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = arg2;
    M2C_FIELD(arg0, s32 *, 0x10) = arg3;
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    func_001ADDF8(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78", func_001ADDF8);

s32 func_001ADE50(void *arg0, s32 arg1, s32 arg2) {
    s32 *temp_7;
    s32 temp_2;
    s32 temp_5;

    temp_5 = arg1 * 4;
    temp_7 = temp_5 + M2C_FIELD(arg0, s32 *, 4);
    temp_2 = (*temp_7 + 0xF) & 0xFFFFFFF0;
    *temp_7 = temp_2 + arg2;
    return ((u32) (M2C_FIELD((temp_5 + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0) + M2C_FIELD(arg0, s32 *, 0xC)) < (u32) M2C_FIELD((temp_5 + M2C_FIELD(arg0, s32 *, 4)), u32 *, 0)) ? 0 : temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78", func_001ADEA8);

void func_001ADF18(void *arg0, s32 arg1) {
    M2C_FIELD(((arg1 * 4) + M2C_FIELD(arg0, s32 *, 4)), s32 *, 0) = 0;
}

void func_001ADF30(void *arg0, s32 arg1) {
    s32 temp_5;

    temp_5 = arg1 * 4;
    M2C_FIELD((temp_5 + M2C_FIELD(arg0, s32 *, 4)), s32 *, 0) = M2C_FIELD((temp_5 + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1add78", func_001ADF50);
