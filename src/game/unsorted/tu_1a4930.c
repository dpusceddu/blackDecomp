#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001A4930(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A4930);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A4F70);

void func_001A4FA8(void) {
    func_001A4930(1, 0xFFFF);
}

void func_001A4FC8(void) {
    func_001A4930(0, 0xFFFF);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001A4FE8);
