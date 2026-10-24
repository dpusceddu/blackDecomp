#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035C6EC(s32, M2C_UNK, M2C_UNK);
extern f32 D_003BD3A8;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1788);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1840);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E18B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1A70);

s32 func_001E1BA0(void *arg0) {
    func_0035C6EC(arg0 + 0x20, 0, 0x28);
    M2C_FIELD(arg0, s32 *, 0x5C) = 7;
    return 1;
}

void func_001E1BE0(void *arg0, s128 arg1, f32 fparg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg0, void **, 0x58);
    if (temp_2 != NULL) {
        M2C_FIELD(arg0, s128 *, 0x10) = arg1;
        if (M2C_FIELD(temp_2, u8 *, 0xAC) != 0) {
            if (M2C_FIELD(arg0, s32 *, 0x5C) == 2) {
                func_001E1EB8();
            }
            M2C_FIELD(arg0, s8 *, 0x7C) = 1;
        } else {
            M2C_FIELD(arg0, s8 *, 0x79) = 1;
        }
        M2C_FIELD(arg0, f32 *, 0x64) = fparg0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1C50);

void func_001E1EA8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x5C) = 6;
}

void func_001E1EB8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x68) = 0;
    M2C_FIELD(arg0, s32 *, 0x5C) = 3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1EC8);

f32 func_001E1F18(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x58), f32 *, 0xA0);
}

f32 func_001E1F28(void) {
    return D_003BD3A8;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E1F38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E2020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E2540);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E26D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E27D8);
