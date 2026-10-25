#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193B40();

s32 func_00193B98(void *arg0) {
    return func_00193B40(arg0) + 0xC;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_193978_193b98", func_00193BB8);
