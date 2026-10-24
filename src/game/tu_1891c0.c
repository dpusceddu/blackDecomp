#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00179258();
extern s32 D_0040F4D4;
extern s32 func_00178F18();
extern s32 func_00176310();
extern s32 func_00173610();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001891C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00189208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00189250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001892C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001892C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00189310);

void * func_001893A0(void *arg0) {
    return (M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0 + 0x20;
}

s32 func_001893B8(s32 arg0, s32 arg1) {
    s32 temp_21;
    s32 temp_2;
    s32 temp_5;
    s32 var_17;
    s32 var_20;

    var_20 = 0;
    if (arg1 != 0) {
        var_17 = arg0;
        temp_21 = var_17 + 0x120;
        do {
            temp_5 = M2C_FIELD(var_17, s32 *, 0);
            if (temp_5 != -1) {
                temp_2 = func_00179258(D_0040F4D4 + 0xFA8, temp_5);
                if ((func_00178F18(temp_2) != 0) && (func_00176310(D_0040F4D4 + 0xFA0, M2C_FIELD(temp_2, s32 *, 8), arg1) != 0)) {
                    var_20 = (var_20 + 1) & 0xFF;
                }
            }
            var_17 += 0x60;
        } while (var_17 < temp_21);
    }
    return var_20;
}

void * func_00189478(void *arg0) {
    return (M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0 + 0x30;
}

s32 func_00189490(s32 arg0) {
    return (func_00173610((M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0 + 0x50) ^ 1) & 0xFF;
}
