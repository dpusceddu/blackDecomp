#include "ps2/prelude.h"

extern M2C_UNK D_003E0128;
extern s32 func_00107D48();
extern M2C_UNK D_003E0110;
extern M2C_UNK D_003E00F8;
extern M2C_UNK D_003E00B0;
extern M2C_UNK D_003E00C8;
extern M2C_UNK D_003E00E0;

s32 func_00383B50(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E0128;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E0128;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 func_00383B80(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E0110;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E0110;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 func_00383BB0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E00F8;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E00F8;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 func_00383BE0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E00B0;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E00B0;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 func_00383C10(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E00C8;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E00C8;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 func_00383C40(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E00E0;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E00E0;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}
