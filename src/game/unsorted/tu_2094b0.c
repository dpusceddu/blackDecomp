#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_002094B0(void *arg0) {
    s32 var_2;
    void *var_4;

    var_4 = arg0;
    var_2 = 0x6D;
    do {
        M2C_FIELD(var_4, s32 *, 0) = 0;
        var_2 -= 1;
        M2C_FIELD(var_4, s32 *, 4) = 0;
        var_4 = (void *) (((s8 *) var_4) + 8);
    } while (var_2 >= 0);
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0", func_002094D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0", func_00209618);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0", func_002096A8);
