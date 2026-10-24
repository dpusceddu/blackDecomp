#include "include_asm.h"
#include "ps2/prelude.h"

void func_00103818(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x21088) = 2;
}

void func_00103830(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x2108C) = 1;
}

void func_00103848(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x2108C) = 2;
}

u8 func_00103860(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x210C9);
}

u8 func_00103870(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x210C8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00103880);

s32 func_00103890(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x21090) == 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001038A8);
