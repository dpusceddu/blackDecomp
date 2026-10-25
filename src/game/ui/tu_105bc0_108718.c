#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00107BC0();
extern M2C_UNK D_0040F0F0;

void func_00108718(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_3;
    s32 var_5;

    var_5 = arg1;
    var_3 = 0;
    if (arg2 > 0) {
loop_1:
        var_3 += 1;
        if (M2C_FIELD(var_5, s32 *, 0) == 0) {
            M2C_FIELD(var_5, s32 *, 0) = arg3;
            return;
        }
        var_5 += 4;
        if (var_3 >= arg2) {

        } else {
            goto loop_1;
        }
    }
}

void func_00108748(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_5;
    s32 var_16;
    s32 var_17;

    if (arg2 > 0) {
        var_16 = arg1;
        var_17 = arg2;
        do {
            temp_5 = M2C_FIELD(var_16, s32 *, 0);
            if ((temp_5 != 0) && (func_00107BC0((s32) &D_0040F0F0, temp_5) == arg3)) {
                M2C_FIELD(var_16, s32 *, 0) = 0;
            }
            var_17 -= 1;
            var_16 += 4;
        } while (var_17 != 0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_105bc0_108718", func_001087C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ui/tu_105bc0_108718", func_001087C8);
