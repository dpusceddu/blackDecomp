#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002599D8(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002599D8);

void func_00259D68(void) {
    func_002599D8(1, 0xFFFF);
}

void func_00259D88(void) {
    func_002599D8(0, 0xFFFF);
}
