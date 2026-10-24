#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003BE8FC;

void func_0021AD98(s32 arg0) {
    D_003BE8FC = arg0;
}

s32 func_0021ADA8(void) {
    return D_003BE8FC;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0021ADB8);
