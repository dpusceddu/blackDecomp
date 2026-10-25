#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_001EAA20(void *, s32, s32, void *, u16);

s32 func_001EA8E0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, f32 fparg0) {
    s32 temp_5;
    s32 var_2;
    void *temp_3;

    temp_3 = M2C_FIELD(arg1, void **, 0x110);
    var_2 = -1;
    if (temp_3 != NULL) {
        temp_5 = M2C_FIELD(temp_3, s32 *, 0x10);
        if ((temp_5 != -1) && (M2C_FIELD(temp_3, f32 *, 8) <= fparg0)) {
            var_2 = func_001EAA20(arg0, temp_5, M2C_FIELD(temp_3, s32 *, 0xC), arg1, M2C_FIELD(temp_3, u16 *, 0x1C));
        }
    }
    return var_2;
}


#include "ps2/recovered_types.h"

s32 func_001EAB60(void *arg0) {
    s32 *var_3;
    s32 temp_2;
    s32 var_5;
    s32 var_6;

    var_6 = 0;
    var_3 = (s32 *) (((s8 *) arg0) + 4);
    var_5 = 7;
    do {
        temp_2 = *var_3 - 1;
        *var_3 = temp_2;
        if (temp_2 > 0) {
            var_6 += 1;
        } else {
            *var_3 = 0;
        }
        var_5 -= 1;
        var_3 = (s32 *) (((s8 *) var_3) + 8);
    } while (var_5 >= 0);
    M2C_FIELD(arg0, s32 *, 0x44) = var_6;
    return temp_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EB4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EB838);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EB998);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBC88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBD88);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBEB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBF68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EBFC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EC060);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EC0B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EC158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EC248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1ea780_1ea8e0", func_001EC330);
