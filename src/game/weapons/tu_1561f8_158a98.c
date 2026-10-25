#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 D_0040EAF8;
extern M2C_UNK D_0048F6D0;

s32 func_00158A98(void *arg0) {
    s32 *temp_3;
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_5 == 0) {
        return 1;
    }
    if (D_0040EAF8 < 8) {
        temp_3 = (D_0040EAF8 * 4) + ((s32) &D_0048F6D0);
        D_0040EAF8 += 1;
        *temp_3 = temp_5;
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/weapons/tu_1561f8_158a98", func_00158AE0);
