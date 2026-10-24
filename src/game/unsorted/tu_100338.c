#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00100338(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00100338);

void func_00100470(void) {
    func_00100338(1, 0xFFFF);
}

void func_00100490(void) {
    func_00100338(0, 0xFFFF);
}
