#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00172418();

void func_001723E8(void *arg0) {
    if (func_00172418() != 0) {
        M2C_FIELD(arg0, s8 *, 0x1B5) = 1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1723e8", func_00172418);
