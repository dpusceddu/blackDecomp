#include "include_asm.h"
#include "ps2/prelude.h"

extern void * func_00354F58();
extern s32 func_00353550();

void * func_00354E78(void *arg0, u32 arg1) {
    s32 temp_3;
    s32 var_4;
    u32 var_3;
    void *temp_2;
    void *temp_3_2;
    void *temp_5;
    void *var_17;

    var_3 = 0;
    var_17 = NULL;
    var_4 = 0;
    if (M2C_FIELD(arg0, s32 *, 0x4BC) == 0) {
        var_17 = func_00354F58(arg0);
        if (var_17 != NULL) {
            func_00353550(arg0, var_17, 1);
            var_4 = 1;
            var_3 = M2C_FIELD(var_17, s32 *, 4) & 0x7FFFFFF8;
            goto block_3;
        }
    } else {
block_3:
        if ((var_17 != NULL) && (arg1 < var_3)) {
            temp_3 = var_3 - arg1;
            M2C_FIELD(var_17, s32 *, 4) = (s32) (arg1 | 1);
            temp_5 = var_17 + arg1;
            M2C_FIELD(temp_5, u32 *, 0) = arg1;
            M2C_FIELD(temp_5, s32 *, 4) = temp_3;
            M2C_FIELD((temp_5 + temp_3), s32 *, 0) = temp_3;
            if (var_4 != 0) {
                func_00353550(arg0, temp_5, 0);
            } else {
                temp_2 = arg0 + 0x30;
                temp_3_2 = M2C_FIELD(temp_2, void **, 0xC);
                M2C_FIELD(temp_5, void **, 8) = temp_2;
                M2C_FIELD(temp_5, void **, 0xC) = temp_3_2;
                M2C_FIELD(temp_2, void **, 0xC) = temp_5;
                M2C_FIELD(temp_3_2, void **, 8) = temp_5;
            }
        }
    }
    return var_17;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00354F58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355080);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003550E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00355268);
