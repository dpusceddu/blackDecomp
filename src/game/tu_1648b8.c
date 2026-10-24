#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00169EB8();

s32 func_001648B8(void) {
    func_00169EB8();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001648D8);
