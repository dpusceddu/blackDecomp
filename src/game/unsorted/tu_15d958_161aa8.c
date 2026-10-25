#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 * func_00160E70(s32 *);
extern s32 * func_00107D20(s32);

s32 * func_00161AA8(s32 *arg0, s32 arg1) {
    s32 *temp_2;
    s32 *temp_2_2;

    temp_2_2 = func_00160E70(arg0);
    if (arg1 <= 0) {
        M2C_FIELD(arg0, s32 **, 0x24) = NULL;
        return temp_2_2;
    }
    temp_2 = func_00107D20(arg1 * 4);
    M2C_FIELD(arg0, s32 **, 0x24) = temp_2;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_161aa8", func_00161AF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_161aa8", func_00161CD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_161aa8", func_00161CE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_161aa8", func_00161D78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_15d958_161aa8", func_00161DE8);
