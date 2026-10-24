#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00211450();
extern s32 func_00210FE8();

void func_00211580(void) {
    func_00211450();
    func_00210FE8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002115A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00211670);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00211888);
