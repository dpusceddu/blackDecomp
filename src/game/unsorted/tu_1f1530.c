#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F1A00();
extern s32 func_001F1A70(s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F1530);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F1608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F1660);

s32 func_001F19D0(s32 arg0) {
    func_001F1A00();
    func_001F1A70(arg0);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001F1A00);
