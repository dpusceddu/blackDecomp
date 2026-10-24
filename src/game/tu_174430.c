#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00165B98();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00174578);

s32 func_001746A0(void) {
    func_00165B98();
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001746C0);
