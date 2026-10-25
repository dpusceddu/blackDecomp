#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_0031D4A0();
extern s32 func_0031D4C8();

s32 func_0031D460(void) {
    func_0031D4A0();
    return 1;
}

void func_0031D480(void) {
    func_0031D4C8();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d460", func_0031D4A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d460", func_0031D4C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d460", func_0031D510);
