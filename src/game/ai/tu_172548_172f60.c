#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00173228(void *, s32);

s32 func_00172F60(void *arg0, s32 arg1) {
    s32 var_3;
    s8 *var_2;

    if (M2C_FIELD(arg0, s8 *, 0x44) == (s8) arg1) {
        M2C_FIELD(arg0, s32 *, 0x40) = 0;
        M2C_FIELD(arg0, s8 *, 0x44) = -1;
    }
    func_00173228(arg0, arg1 << 0x18);
    var_3 = 3;
    var_2 = (s8 *) (((s8 *) ((void *) (((s8) arg1 * 0xC0) + ((s8 *) arg0)))) + 0x134);
    do {
        *var_2 = 0;
        var_3 -= 1;
        var_2 = (s8 *) (((s8 *) var_2) + -0x30);
    } while (var_3 >= 0);
    return (s32) var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548_172f60", func_00172FE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548_172f60", func_00173028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548_172f60", func_00173168);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548_172f60", func_00173198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548_172f60", func_00173228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/ai/tu_172548_172f60", func_00173370);
