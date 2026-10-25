#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_001394B8(void *arg0, s32 arg1) {
    s32 *var_4;
    s32 temp_2;
    s32 var_3;

    var_4 = (s32 *) (((s8 *) arg0) + 0x79D4);
    var_3 = 7;
    do {
        temp_2 = *var_4;
        var_3 -= 1;
        if (temp_2 == arg1) {
            *var_4 = 0;
        }
        var_4 = (s32 *) (((s8 *) var_4) + 8);
    } while (var_3 >= 0);
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_1394b8", func_001394E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_1394b8", func_00139538);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_1394b8", func_00139698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_1394b8", func_001396F0);
