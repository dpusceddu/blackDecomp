#include "ps2/prelude.h"

extern M2C_UNK D_003E00F8;
extern s32 func_00107D48();
extern s32 D_0049B518;
extern s32 * func_0038D240();
extern s32 func_00370168();
extern s32 D_0040EBF8;
extern M2C_UNK D_003E4728;
extern s32 D_0049B528;
extern s32 func_0038A008();
extern M2C_UNK D_0040EBD8;
extern u8 D_003C8980;

s32 func_0038CE00(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E00F8;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E00F8;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 * func_0038CE30(void) {
    if (D_0049B518 == 0) {
        func_0038D240();
        func_00370168(&D_0049B518, "Q24Kaim12CEntityClass", &D_0040EBF8);
    }
    return &D_0049B518;
}

s32 func_0038CE80(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E4728;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E4728;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 * func_0038CEB0(void) {
    if (D_0049B528 == 0) {
        func_0038A008();
        func_00370168(&D_0049B528, "Q24Kaim21CEntityAttributeClass", &D_0040EBD8);
    }
    return &D_0049B528;
}

void * func_0038CF00(void *arg0) {
    if (D_003C8980 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003C8980 = 0;
    return arg0;
}
