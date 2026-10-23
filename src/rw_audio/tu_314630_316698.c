#include "auto/prelude.h"

extern s32 func_00312C70();
extern s32 func_00317C20(M2C_UNK *, void *);
extern M2C_UNK D_004563D0;

void * func_00316698(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 4);
    if ((temp_4 != NULL) && (M2C_FIELD(arg0, s32 *, 8) & 2)) {
        func_00312C70(temp_4);
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & 0xFFFFFFFD);
    }
    return arg0;
}

void * func_003166F8(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0);
    if ((temp_5 != NULL) && (M2C_FIELD(arg0, s32 *, 8) & 1)) {
        func_00317C20(&D_004563D0, temp_5);
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) & 0xFFFFFFFE);
    }
    return arg0;
}

void * func_00316758(void *arg0) {
    M2C_FIELD(arg0, s32 *, 8) = 0;
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
    return arg0;
}
