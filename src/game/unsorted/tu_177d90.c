#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00173640(void *, f32);
extern s32 func_0017B8A8();
extern void * D_0040F4D4;
extern s32 func_00177C78();

void func_00177D90(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177D98);

void func_00177DD8(s128 *arg0, s128 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177DE0);

void func_00177E60(s128 *arg0, s128 arg1) {
    *arg0 = arg1;
}

void func_00177E68(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x60) = arg1;
}

void func_00177E70(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x58) = arg1;
    func_00173640(arg0 + 0x5C, 5.0f);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177E98);

void func_00177EE8(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_3;

    temp_3 = 1 << arg1;
    if (arg2 != 0) {
        M2C_FIELD(arg0, s32 *, 0x64) = (s32) (M2C_FIELD(arg0, s32 *, 0x64) | temp_3);
        return;
    }
    M2C_FIELD(arg0, s32 *, 0x64) = (s32) (M2C_FIELD(arg0, s32 *, 0x64) & ~temp_3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177F18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00177F60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001780B8);

u8 func_00178348(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x50);
}

void func_00178350(void *arg0, s128 arg1, f32 fparg0) {
    s32 temp_2;

    M2C_FIELD(arg0, f32 *, 0x50) = fparg0;
    M2C_FIELD(arg0, s128 *, 0) = arg1;
    temp_2 = func_0017B8A8(D_0040F4D4 + 0x1290);
    if (temp_2 != 0) {
        func_00177C78(temp_2, arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00178398);
