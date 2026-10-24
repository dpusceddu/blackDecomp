#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00282628();

s32 func_001ED478(void) {
    func_00282628();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001ED498);
