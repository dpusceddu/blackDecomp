#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern M2C_UNK D_003DC428;
extern M2C_UNK D_003DC388;

s32 * func_00382E78(s32 *arg0) {
    s32 *var_3;
    s32 *var_3_2;
    s32 var_5;
    s32 var_5_2;

    var_3 = arg0;
    var_5 = 0x1F;
    do {
        M2C_FIELD(var_3, M2C_UNK **, 0x10) = &D_003DC428;
        var_5 -= 1;
        var_3 = (s32 *) (((s8 *) var_3) + 0x120);
    } while (var_5 != -1);
    var_3_2 = (s32 *) (((s8 *) arg0) + 0x2400);
    var_5_2 = 0xF;
    do {
        M2C_FIELD(var_3_2, M2C_UNK **, 0x10) = &D_003DC388;
        var_5_2 -= 1;
        var_3_2 = (s32 *) (((s8 *) var_3_2) + 0x120);
    } while (var_5_2 != -1);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500_382e78", func_00382EE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500_382e78", func_00382F90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500_382e78", func_003830D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500_382e78", func_00383228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_382500_382e78", func_003836E8);
