#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00118088();

s32 func_00118290(void *arg0, void *arg1) {
    func_00118088();
    M2C_FIELD(arg1, s128 *, 0x20) = (s128) M2C_FIELD(arg0, s128 *, 0x20);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_118290", func_001182D0);
