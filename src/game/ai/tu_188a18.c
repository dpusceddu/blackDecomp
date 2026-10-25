#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00188A40();

s32 func_00188A18(s32 arg0, s32 arg1) {
    s32 var_2;

    var_2 = M2C_FIELD(arg0, s32 *, 8);
    if (var_2 == arg1) {
        var_2 = func_00188A40(arg0, -1);
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_188a18", func_00188A40);
