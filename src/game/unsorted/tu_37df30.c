#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0037DF30(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037DF30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0037E078);

void func_0037E678(void) {
    func_0037DF30(1, 0xFFFF);
}

void func_0037E698(void) {
    func_0037DF30(0, 0xFFFF);
}
