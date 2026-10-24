#include "ps2/prelude.h"

extern s32 D_004512A8;
extern M2C_UNK * func_0038D4A0();
extern M2C_UNK D_0049B538;
extern s32 func_0035E690();
extern M2C_UNK func_002E5278;
extern s32 D_0049B950;
extern s32 * func_0038E6E0();
extern s32 func_00370168();
extern s32 D_0049AB98;
extern s32 D_0040EC00;
extern s32 func_00370188();
extern M2C_UNK D_003E00C8;
extern s32 func_00107D48();
extern s32 D_0049B960;
extern s32 * func_0038D650();
extern s32 D_0040EC08;

M2C_UNK * func_0038D338(void) {
    if (D_004512A8 == 0) {
        func_0038D4A0(&D_0049B538);
        D_004512A8 = 1;
        func_0035E690(&func_002E5278);
    }
    return &D_0049B538;
}

void * func_0038D390(void) {
    if (D_0049B950 == 0) {
        func_0038E6E0();
        func_00370168(&D_0049B950, "Q24Kaim13CBrainService", &D_0049AB98);
    }
    return &D_0049B950;
}

s32 * func_0038D3E0(void) {
    if (D_0040EC00 == 0) {
        func_00370188(&D_0040EC00, "Q24Kaimt10CMetaClass2ZQ24Kaim13CBrainServiceZPFPQ24Kaim6CBrain_PQ24Kaim13CBrainService");
    }
    return &D_0040EC00;
}

s32 func_0038D420(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_003E00C8;
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E00C8;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

s32 * func_0038D450(void) {
    if (D_0049B960 == 0) {
        func_0038D650();
        func_00370168(&D_0049B960, "Q24Kaim16IConstraintClass", &D_0040EC08);
    }
    return &D_0049B960;
}
