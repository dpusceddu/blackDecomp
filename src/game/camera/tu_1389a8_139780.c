#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00107D20();

void func_00139780(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_3;
    s32 var_5;

    M2C_FIELD(arg0, s32 *, 0xC) = func_00107D20(arg1 * 4);
    var_5 = 0;
    M2C_FIELD(arg0, s32 *, 4) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    if (arg1 > 0) {
        do {
            temp_3 = var_5 * 4;
            var_5 += 1;
            M2C_FIELD((temp_3 + M2C_FIELD(arg0, s32 *, 0xC)), s32 *, 0) = 0;
        } while (var_5 < arg1);
    }
    M2C_FIELD(arg0, s32 *, 0) = arg2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139780", func_001397F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139780", func_00139838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139780", func_001398E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139780", func_00139940);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139780", func_00139980);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/camera/tu_1389a8_139780", func_00139A70);
