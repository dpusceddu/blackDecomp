#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0020D1A8(s32);
extern s32 D_0040F544;

void func_00209340(void) {
    func_0020D1A8(D_0040F544 + 0xE90);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00209368);
