#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035D1A0(M2C_UNK *, s32, M2C_UNK);

void func_0020B8C0(s32 arg0) {
    func_0035D1A0(arg0 + 0x3860, arg0 + 0x3840, 0x20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020B8E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020B950);
