#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_0013B9D0(s32);
extern s32 func_0014DC18(void *);
extern s32 func_001531C8(void *);

s32 func_0012A0D8(s32 arg0) {
    s32 var_16;
    s32 var_17;
    s32 var_17_2;
    void *var_16_2;

    var_16 = arg0 + 0x30;
    var_17 = 0;
    do {
        var_17 -= 1;
        func_0013B9D0(var_16);
        var_16 += 0x8C0;
    } while (var_17 >= 0);
    var_16_2 = arg0 + 0x5ABC;
    var_17_2 = 1;
    do {
        var_17_2 -= 1;
        func_0014DC18(var_16_2);
        var_16_2 = (void *) (((s8 *) var_16_2) + 8);
    } while (var_17_2 >= 0);
    return func_001531C8(arg0 + 0x5ACC);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_127118_12a0d8", func_0012A158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_127118_12a0d8", func_0012A1E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_127118_12a0d8", func_0012A280);
