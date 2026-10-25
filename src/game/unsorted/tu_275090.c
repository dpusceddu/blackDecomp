#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00353F50(s32);

void func_00275090(s32 arg0) {
    func_00353F50(arg0 + 8);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_275090", func_002750B0);
