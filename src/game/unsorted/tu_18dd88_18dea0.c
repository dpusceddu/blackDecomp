#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0018DDD8();

f32 func_0018DEA0(s32 arg0, s32 arg1) {
    switch (arg1) {                                 /* irregular */
    case 0:
        return 0.0f;
    case 1:
        return 30.0f;
    case 2:
        return 10.0f;
    case 3:
        return 40.0f;
    default:
        return 0.0f;
    }
}

s32 func_0018DF28(void) {
    return func_0018DDD8() != 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_18dd88_18dea0", func_0018DF48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_18dd88_18dea0", func_0018E020);
