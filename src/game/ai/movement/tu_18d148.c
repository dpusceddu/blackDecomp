#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00181AD0(void *arg0, s32 arg1);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D148);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D1F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D2F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D368);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D3A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D410);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D4C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D580);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D5D0);

u8 func_0018D608(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x15);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D610);

void func_0018D658(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x15) == 0) {
        M2C_FIELD(arg0, u8 *, 0x15) = 1U;
        func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 9);
    }
}

void func_0018D698(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x18) = arg1;
    func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 0xB);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D6C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D6F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D730);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D768);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0018D7A0);

void func_0018D818(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x50) & 0xEF) {
        M2C_FIELD(arg0, u8 *, 0x50) = 0x10U;
        func_00181AD0(M2C_FIELD(arg0, s32 *, 0x1C) + 0xEC0, 0xD);
    }
}

void func_0018D858(void *arg0) {
    M2C_FIELD(arg0, u8 *, 0x50) = (u8) ((M2C_FIELD(arg0, u8 *, 0x50) & 0xFE) | 2);
}
