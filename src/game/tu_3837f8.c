#include "include_asm.h"
#include "ps2/prelude.h"

void func_003837F8(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0xC4) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00383808);
