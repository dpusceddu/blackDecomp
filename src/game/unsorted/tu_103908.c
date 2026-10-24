#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_00103908(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x2109C);
}

void func_00103918(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x21098) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00103928);
