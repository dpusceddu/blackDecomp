#include "include_asm.h"
#include "ps2/prelude.h"

void func_00180CC8(void *arg0, s8 arg1) {
    M2C_FIELD(arg0, s8 *, 0x14C) = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00180CD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00180CD8);
