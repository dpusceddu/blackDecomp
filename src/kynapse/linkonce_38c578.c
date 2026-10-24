#include "ps2/prelude.h"

extern M2C_UNK D_003E0110;
extern s32 func_00107D48();
extern s32 D_0049B0A0;
extern s32 * func_0038C7A8();
extern s32 func_00370168();
extern s32 D_0040EBF0;
extern u8 D_003C7FA1;

s32 func_0038C578(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E0110;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E0110;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 * func_0038C5A8(void) {
    if (D_0049B0A0 == 0) {
        func_0038C7A8();
        func_00370168(&D_0049B0A0, "Q24Kaim11CBrainClass", &D_0040EBF0);
    }
    return &D_0049B0A0;
}

void * func_0038C5F8(void *arg0) {
    if (D_003C7FA1 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003C7FA1 = 0;
    return arg0;
}
