#include "ps2/prelude.h"

extern M2C_UNK D_003E0128;
extern s32 func_00107D48();
extern s32 D_0049B020;
extern s32 * func_0038B9D0();
extern s32 func_00370168();
extern s32 D_0040EBE8;
extern M2C_UNK D_003E3D38;
extern s32 D_0049B030;
extern s32 func_00389980();
extern M2C_UNK D_0040EBD0;
extern u8 D_003C7784;

s32 func_0038B590(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E0128;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E0128;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 * func_0038B5C0(void) {
    if (D_0049B020 == 0) {
        func_0038B9D0();
        func_00370168(&D_0049B020, "Q24Kaim12CActionClass", &D_0040EBE8);
    }
    return &D_0049B020;
}

s32 func_0038B610(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E3D38;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E3D38;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 * func_0038B640(void) {
    if (D_0049B030 == 0) {
        func_00389980();
        func_00370168(&D_0049B030, "Q24Kaim21CActionAttributeClass", &D_0040EBD0);
    }
    return &D_0049B030;
}

void * func_0038B690(void *arg0) {
    if (D_003C7784 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003C7784 = 0;
    return arg0;
}
