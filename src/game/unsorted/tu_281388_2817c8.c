#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00285190(void *);

s32 func_002817C8(s32 arg0) {
    s32 temp_2;
    s32 var_16;
    u32 temp_17;

    var_16 = arg0;
    temp_17 = var_16 + 0xE00;
    do {
        func_00285190((void *) var_16);
        var_16 += 0x38;
        temp_2 = (u32) var_16 < temp_17;
    } while (temp_2 != 0);
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2817c8", func_00281808);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_281388_2817c8", func_00281878);
