#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0020B988();
extern s32 func_0020AFF8();
extern s32 func_00209FF8();
extern s32 func_0027C278();
extern M2C_UNK D_003FA790;
extern M2C_UNK D_003FA7A8;

s32 func_0020B0C0(s32 arg0) {
    s32 temp_16;
    s32 temp_2;

    func_0020B988(arg0, 1);
    func_0020B988(arg0, 3);
    func_0020B988(arg0, 6);
    func_0020B988(arg0, 2);
    if (M2C_FIELD(arg0, s32 *, 0x3924) != 0) {
        func_0020AFF8(arg0);
    }
    temp_16 = arg0 + 0x2530;
    func_00209FF8(temp_16, func_0027C278((s32) &D_003FA790));
    temp_2 = func_00209FF8(temp_16, func_0027C278((s32) &D_003FA7A8));
    M2C_FIELD(arg0, s32 *, 0x37A8) = 0x38;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020B168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020B170);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020B2B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020B678);
