#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0027ACC8();

void func_001178D8(void *arg0) {
    func_0027ACC8();
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_1178d8", func_00117900);
