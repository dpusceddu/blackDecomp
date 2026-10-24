#include "include_asm.h"
#include "ps2/prelude.h"

u8 func_00272308(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x41);
}

void func_00272310(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x42) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00272320);
