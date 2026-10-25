#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0035E750();
extern s32 D_0040F544;
extern M2C_UNK func_00209AA0;

void func_00209A50(void *arg0, M2C_UNK *arg1) {
    M2C_FIELD(arg0, M2C_UNK **, 4) = arg1;
}

void func_00209A58(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

void func_00209A60(void) {
    if (func_0035E750() == 0) {
        func_00209A50(D_0040F544 + 0x44C, &func_00209AA0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_209a50", func_00209AA0);
