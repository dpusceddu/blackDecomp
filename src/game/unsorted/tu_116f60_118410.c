#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00118088();

s32 func_00118410(void) {
    func_00118088();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00118430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001187A8);
