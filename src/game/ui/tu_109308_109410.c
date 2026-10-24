#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035CBC0();
extern s32 func_0035D728();
extern s32 func_001D9250(s32);
extern void * D_0040F510;

void func_00109410(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_16;

    temp_16 = (arg2 * 0x140) + arg0;
    func_0035CBC0(temp_16 + 0x14);
    M2C_FIELD(temp_16, s32 *, 0x114) = arg3;
    M2C_FIELD(temp_16, s32 *, 0x118) = arg4;
    M2C_FIELD(temp_16, s8 *, 0x13A) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109468);

void func_00109488(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    void *temp_4;

    temp_4 = (arg1 * 0x140) + arg0;
    M2C_FIELD(temp_4, s32 *, 0x130) = arg5;
    M2C_FIELD(temp_4, s8 *, 0x139) = 1;
    M2C_FIELD(temp_4, s32 *, 0xC) = 1;
    M2C_FIELD(temp_4, s32 *, 0x11C) = arg2;
    M2C_FIELD(temp_4, s32 *, 0x128) = arg3;
    M2C_FIELD(temp_4, s32 *, 0x12C) = arg4;
    M2C_FIELD(temp_4, s8 *, 0x13C) = 0;
}

void func_001094C0(void *arg0, M2C_UNK *arg1, s32 arg2, s32 arg3) {
    s32 temp_4;

    func_0035D728(arg0 + 0x44, "videos/%s.m2v", arg1);
    func_0035CBC0(arg0 + 0x84, arg1);
    temp_4 = M2C_FIELD(arg0, s32 *, 0x1A8);
    M2C_FIELD(arg0, s32 *, 0x198) = arg3;
    M2C_FIELD(arg0, s8 *, 0x1B8) = 1;
    M2C_FIELD(arg0, s32 *, 0x1B4) = arg2;
    if ((temp_4 != 0x37) && (temp_4 != 1)) {
        M2C_FIELD(arg0, s8 *, 0x1B9) = 1;
    }
}

void func_00109550(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x1A8);
    M2C_FIELD(arg0, s8 *, 0x1B8) = 0;
    if ((temp_3 != 0x37) && (temp_3 != 1)) {
        M2C_FIELD(arg0, s8 *, 0x1B9) = 1;
    }
}

s32 func_00109578(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x1A8) == 0x1C;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109588);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109760);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109AE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109BB0);

s32 func_00109CC0(void) {
    func_001D9250(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x3C));
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109CF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109DC0);

void func_00109E70(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109E78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00109EE0);
