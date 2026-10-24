#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00274FC8(s32);
extern s32 func_00274F80(s32);
extern s32 func_00274F60(s32);

s32 func_00282100(void *arg0) {
    s32 temp_16;

    temp_16 = M2C_FIELD(arg0, s32 *, 0x54);
    if (temp_16 != 1) {
        if (temp_16 < 2) {
            if (temp_16 != 0) {
                return 0;
            }
            goto block_7;
        }
        if (temp_16 != 2) {
            return 0;
        }
        goto block_7;
    }
    func_00282170(arg0);
    M2C_FIELD(arg0, s32 *, 0x54) = temp_16;
block_7:
    return 1;
}

s32 func_00282170(void *arg0) {
    func_00274FC8(arg0 + 0x38);
    M2C_FIELD(arg0, s32 *, 0x54) = 2;
    return 1;
}

s32 func_002821A8(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg2) {                                 /* irregular */
    case 0:
        return func_00274F80(arg0 + 0x1C);
    case 1:
        return func_00274F80(arg0 + 0x38);
    default:
        return 0;
    }
}

void func_002821F0(s32 arg0) {
    func_00274F60(arg0 + 0x38);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00282210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00282218);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00282290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002822C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002825A0);
