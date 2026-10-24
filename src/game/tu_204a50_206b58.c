#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00204FF0();

void func_00206B58(void *arg0) {
    func_00204FF0();
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x1D) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00206B88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00206E30);
