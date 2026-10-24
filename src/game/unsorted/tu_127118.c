#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00108120();
extern s32 D_0040F4C4;
extern s32 func_001B37C8();
extern s32 D_0040F4D8;
extern s32 func_001B61C0();
extern s32 func_0014DD98();
extern s32 func_0014DE58();
extern s32 func_0014DF68();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127550);

s32 func_001276B8(void *arg0, s32 arg1) {
    s32 temp_17;
    s32 temp_5;

    temp_5 = arg1 & 0xFF;
    temp_17 = temp_5 * 4;
    if (M2C_FIELD((temp_17 + M2C_FIELD(arg0, s32 *, 0x5800)), s32 *, 0) == 0) {
        M2C_FIELD((temp_17 + M2C_FIELD(arg0, s32 *, 0x5800)), s32 *, 0) = func_00108120(D_0040F4C4, M2C_FIELD(((temp_5 * 0x18) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x5844), s32 *, 8)), s64 *, 8));
    }
    return M2C_FIELD((temp_17 + M2C_FIELD(arg0, s32 *, 0x5800)), s32 *, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127738);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001277A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127A40);

void func_00127AB8(void) {

}

void func_00127AC0(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127AC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00127CF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00128008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00128120);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001282B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001282B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001282C8);

s32 func_001282D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 4) + arg0;
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001282E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00128480);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129108);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00129160);

void * func_001291C0(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    return func_0014DD98(arg0 + (((s32) arg1 * 8) + 0x5ABC), arg1, arg2, arg3, arg4);
}

void * func_001291E8(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5) {
    return func_0014DE58(arg0 + (((s32) arg1 * 8) + 0x5ABC), arg1, arg2, arg3, arg4, M2C_FIELD(arg2, void **, 0x38), M2C_FIELD(arg2, void **, 0x40), arg5);
}

void * func_00129218(void *arg0, void *arg1, void *arg2) {
    return func_0014DF68(arg0 + (((s32) arg1 * 8) + 0x5ABC), arg2);
}
