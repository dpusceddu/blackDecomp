#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001B37C8(s32, u16);
extern s32 D_0040F4D8;

void func_00152878(void *arg0) {
    if (M2C_FIELD(arg0, u16 *, 0x1BC) != 0xFFFF) {
        func_001B37C8(D_0040F4D8 + 0x33C40, M2C_FIELD(arg0, u16 *, 0x1BC));
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68_152878", func_001528B8);
