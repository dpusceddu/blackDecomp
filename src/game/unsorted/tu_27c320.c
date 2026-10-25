#include "include_asm.h"
#include "ps2/prelude.h"

void func_0027C320(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

void func_0027C328(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x14) != 0) {
        M2C_FIELD(arg0, u8 *, 0x14) = 0U;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_27c320", func_0027C340);
