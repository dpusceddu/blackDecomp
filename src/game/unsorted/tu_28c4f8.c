#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"

s32 func_0028C4F8(s32 arg0, s32 arg1) {
    s32 var_2;
    s32 var_4;

    var_4 = arg0;
    var_2 = -1;
    if (var_4 != 0) {
        do {
            var_4 = (s32) ((u32) var_4 >> 1);
            var_2 += 1;
        } while (var_4 != 0);
    }
    return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_28c4f8", func_0028C520);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_28c4f8", func_0028C728);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_28c4f8", func_0028D888);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_28c4f8", func_0028D920);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_28c4f8", func_0028EE88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_28c4f8", func_0028EE98);
