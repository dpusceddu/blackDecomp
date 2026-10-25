#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_00149120(s32 *arg0, s32 arg1) {
    s32 var_3;
    s32 var_5;

    var_5 = arg1;
    var_3 = 0;
    if (var_5 != -1) {
        do {
            var_5 = M2C_FIELD(((var_5 * 4) + M2C_FIELD(M2C_FIELD(arg0, void **, 0x118), s32 *, 0x58)), s32 *, 0);
            var_3 += 1;
        } while (var_5 != -1);
    }
    return var_3;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_149120", func_00149178);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_149120", func_001491B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_149120", func_00149210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/actor/tu_1448c8_149120", func_00149260);
