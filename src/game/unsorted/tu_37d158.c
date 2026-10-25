#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0037D158(M2C_UNK, M2C_UNK);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37d158", func_0037D158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_37d158", func_0037D2A0);

void func_0037D840(void) {
    func_0037D158(1, 0xFFFF);
}

void func_0037D860(void) {
    func_0037D158(0, 0xFFFF);
}
