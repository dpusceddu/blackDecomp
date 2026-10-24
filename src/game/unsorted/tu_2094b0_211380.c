#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00211450();
extern s32 func_00210FE8();
extern s32 func_00211670();
extern s32 func_00211888();

void func_00211380(void) {
    func_00211450();
    func_00210FE8();
    func_00211670();
    func_00211888();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002113B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00211420);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00211450);
