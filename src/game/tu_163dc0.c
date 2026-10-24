#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00165B98();

s32 func_00163DC0(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00163DE0);
