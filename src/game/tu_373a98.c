#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00377628(s32);
extern s32 func_00311B50();
extern s32 func_00377840();
extern s32 func_00322C70();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00373A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00373C18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00373DC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00373F20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00374090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00374140);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00374180);

void func_00374188(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        func_00377628(arg0 + 0x84);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003741A8);

s32 func_00374348(s32 arg0, s32 arg1, s32 arg2) {
    func_00374188(arg0, 1);
    func_00311B50(M2C_FIELD(arg0, s32 *, 0x80));
    func_00377840(arg0 + 0x84);
    return func_00322C70(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003743A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00374458);
