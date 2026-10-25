#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_001777D0(void *);

s32 func_001771F0(void *arg0) {
    s32 var_2;
    void *var_16;

    func_001777D0(arg0);
    var_16 = (void *) (((s8 *) arg0) + 0x980);
    var_2 = 4;
    do {
        M2C_FIELD(var_16, s32 *, -4) = 0;
        var_2 -= 1;
        M2C_FIELD(var_16, s32 *, 0) = 0;
        var_16 = (void *) (((s8 *) var_16) + 8);
    } while (var_2 >= 0);
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_177148_1771f0", func_00177258);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_177148_1771f0", func_00177350);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_177148_1771f0", func_00177470);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_177148_1771f0", func_001776A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_177148_1771f0", func_00177750);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_177148_1771f0", func_00177780);
