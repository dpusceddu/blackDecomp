#include "include_asm.h"
#include "ps2/prelude.h"

void func_001A3110(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xC0) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A3120);
