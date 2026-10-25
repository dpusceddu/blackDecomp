#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0037E6B8(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37e6b8", func_0037E6B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37e6b8", func_0037E800);

void func_0037EC10(void) {
    func_0037E6B8(1, 0xFFFF);
}

void func_0037EC30(void) {
    func_0037E6B8(0, 0xFFFF);
}
