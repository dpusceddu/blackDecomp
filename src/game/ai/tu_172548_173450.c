#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern void * D_0040F4D0;

s32 func_00173450(void *arg0, s128 arg1) {
    s32 var_3;
    s128 *var_2;

    var_3 = 2;
    var_2 = (s128 *) (((s8 *) arg0) + 0x20);
    do {
        *var_2 = (s128) arg1;
        var_3 -= 1;
        var_2 = (s128 *) (((s8 *) var_2) + -0x10);
    } while (var_3 >= 0);
    M2C_FIELD(arg0, f32 *, 0x30) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001735E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00173640);
