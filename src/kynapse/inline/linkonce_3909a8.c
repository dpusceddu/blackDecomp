#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_0049BBB0;
extern s32 * func_00390B58();
extern s32 func_00370168();
extern s32 D_0049BBE0;
extern s32 D_0040EC30;
extern s32 func_00370188();
extern M2C_UNK D_004075A8;
extern M2C_UNK D_003E00B0;
extern s32 func_00107D48();

s32 * func_003909A8(void) {
    if (D_0049BBB0 == 0) {
        func_00390B58();
        func_00370168(&D_0049BBB0, "Q24Kaim11CConstraint", &D_0049BBE0);
    }
    return &D_0049BBB0;
}

s32 * func_003909F8(void) {
    if (D_0040EC30 == 0) {
        func_00370188(&D_0040EC30, &D_004075A8);
    }
    return &D_0040EC30;
}

s32 func_00390A38(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E00B0;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E00B0;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}
