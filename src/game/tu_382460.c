#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00313008();
extern s32 func_00313048();

void func_00382460(void) {
    func_00313008();
}

void func_00382480(void) {
    func_00313048();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003824A0);
