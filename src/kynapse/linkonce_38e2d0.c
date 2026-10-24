#include "ps2/prelude.h"

extern M2C_UNK D_003EA7E8;
extern s32 func_00107D48();
extern s32 D_0049BA30;
extern s32 * func_0038E5F8();
extern s32 func_00370168();
extern s32 D_0040EC18;
extern s32 D_0040EC10;
extern s32 func_00370188();
extern M2C_UNK D_00406A50;
extern M2C_UNK D_003EA790;

s32 func_0038E2D0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003EA7E8;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EA7E8;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 * func_0038E300(void) {
    if (D_0049BA30 == 0) {
        func_0038E5F8();
        func_00370168(&D_0049BA30, "Q24Kaim27CPointContainerWrapperClass", &D_0040EC18);
    }
    return &D_0049BA30;
}

s32 * func_0038E350(void) {
    if (D_0040EC10 == 0) {
        func_00370188(&D_0040EC10, &D_00406A50);
    }
    return &D_0040EC10;
}

s32 func_0038E390(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003EA790;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EA790;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}
