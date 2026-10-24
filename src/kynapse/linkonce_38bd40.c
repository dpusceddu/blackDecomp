#include "ps2/prelude.h"

extern u8 D_003E7C08;
extern s32 D_00451214;
extern M2C_UNK D_003E7800;
extern s32 func_0035E690(M2C_UNK *);
extern M2C_UNK func_002E1508;
extern u8 D_003E8018;
extern s32 D_00451218;
extern M2C_UNK D_003E7C10;
extern M2C_UNK func_002E1518;
extern u8 D_003E8428;
extern s32 D_0045121C;
extern M2C_UNK D_003E8020;
extern M2C_UNK func_002E1538;

M2C_UNK * func_0038BD40(M2C_UNK *arg0) {
    if (D_003E7C08 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003E7C08 = 0;
    return arg0;
}

M2C_UNK * func_0038BD60(void) {
    if (D_00451214 == 0) {
        func_0038BD40(&D_003E7800);
        D_00451214 = 1;
        func_0035E690(&func_002E1508);
    }
    return &D_003E7800;
}

M2C_UNK * func_0038BDB8(M2C_UNK *arg0) {
    if (D_003E8018 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003E8018 = 0;
    return arg0;
}

M2C_UNK * func_0038BDD8(void) {
    if (D_00451218 == 0) {
        func_0038BDB8(&D_003E7C10);
        D_00451218 = 1;
        func_0035E690(&func_002E1518);
    }
    return &D_003E7C10;
}

M2C_UNK * func_0038BE30(M2C_UNK *arg0) {
    if (D_003E8428 != 0) {
        M2C_FIELD(arg0, s32 *, 0x400) = 0;
    }
    D_003E8428 = 0;
    return arg0;
}

M2C_UNK * func_0038BE50(void) {
    if (D_0045121C == 0) {
        func_0038BE30(&D_003E8020);
        D_0045121C = 1;
        func_0035E690(&func_002E1538);
    }
    return &D_003E8020;
}
