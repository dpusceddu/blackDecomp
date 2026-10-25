#include "include_asm.h"
#include "ps2/prelude.h"

void * func_00123C90(void *arg0, void *arg1, void *arg2) {
    return arg0 + (((s32) (arg1 + ((s32) arg2 * 8)) << 5) + 4);
}

s32 func_00123CA8(void) {
    return 0;
}

s32 func_00123CB0(void) {
    return 0;
}

s32 func_00123CB8(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_120068_123c90", func_00123CC0);
