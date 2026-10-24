#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_0020BC00(void *arg0, s32 arg1) {
    return arg0 + ((arg1 * 0x8C4) + 0x13A8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0020BC18);
