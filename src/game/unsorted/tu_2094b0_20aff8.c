#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001084A8(s32, M2C_UNK, M2C_UNK);
extern s32 D_0040F4C4;
extern s32 func_001438E8(s32);
extern s32 D_0040F540;

void func_0020AFF8(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x36E8) != 0) {
        func_001084A8(D_0040F4C4, 7, 0xC);
        M2C_FIELD(arg0, s32 *, 0x36E8) = 0;
    }
    M2C_FIELD(arg0, s32 *, 0x3924) = 0;
    func_001438E8(D_0040F540);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_20aff8", func_0020B048);
