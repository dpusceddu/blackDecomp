#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_00294840(void *, s32, s32);
extern s32 func_002946D0(void *, s32, s32);

s32 func_00294CE8(void *arg0, s32 arg1, s32 arg2) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), s32 *, 0x184) != 3) {
        return func_00294840(arg0, arg1, arg2);
    }
    return func_002946D0(arg0, arg1, arg2);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00294D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00294D88);

#include "ps2/recovered_types.h"
extern s32 * func_00296468(s32 *, s32 *);
extern s32 func_00297688(s32 *);

s32 func_00294DB0(s32 *arg0) {
    s32 temp_2;
    void *var_17;

    if ((M2C_FIELD(arg0, s32 *, 0x184) == 3) && (M2C_FIELD(arg0, s32 *, 0x130) != 0)) {
        func_00296468(arg0, "odd number of field pictures");
        M2C_FIELD(arg0, s32 *, 0x130) = 0;
    }
    switch (M2C_FIELD(arg0, s32 *, 0x184)) {        /* irregular */
    case 3:
        var_17 = M2C_FIELD(arg0, void **, 0x1D0);
        break;
    case 1:
        var_17 = M2C_FIELD(arg0, void **, 0x1E0);
        break;
    case 2:
        var_17 = M2C_FIELD(arg0, void **, 0x1F0);
        break;
    default:
        var_17 = M2C_FIELD(arg0, void **, 0x1D0);
        func_00296468(arg0, "unknown picture sutructure");
        break;
    }
    temp_2 = func_00297688(arg0);
    if (temp_2 != 0) {
        M2C_FIELD(var_17, s32 *, 0x28) = 1;
    }
    return temp_2;
}
