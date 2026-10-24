#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00339A90();
extern s32 func_00339A90(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00339A90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00339BD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00339C00);

void func_00339C28(void) {
    func_00339A90(1, 0xFFFF);
}

void func_00339C48(void) {
    func_00339A90(0, 0xFFFF);
}
