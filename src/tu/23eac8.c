#include "auto/prelude.h"

extern s32 func_00386668();
extern s32 func_00386698();

void func_0023EAC8(s32 arg0, void *arg1, void *arg2) {
    void *temp_2;

    temp_2 = M2C_FIELD(arg1, void **, 8);
    M2C_FIELD(arg2, void **, 0xC) = arg1;
    M2C_FIELD(arg2, void **, 8) = temp_2;
    if (temp_2 != NULL) {
        M2C_FIELD(temp_2, void **, 0xC) = arg2;
    }
    M2C_FIELD(M2C_FIELD(arg2, void **, 0xC), void **, 8) = arg2;
}

void func_0023EAE8(s32 arg0, s32 *arg1) {
    void *temp_2;
    void *temp_3;
    void *temp_3_2;

    temp_3 = M2C_FIELD(arg1, void **, 0xC);
    if (temp_3 != NULL) {
        M2C_FIELD(temp_3, void **, 8) = (void *) M2C_FIELD(arg1, void **, 8);
    }
    temp_3_2 = M2C_FIELD(arg1, void **, 8);
    if (temp_3_2 != NULL) {
        M2C_FIELD(temp_3_2, void **, 0xC) = (void *) M2C_FIELD(arg1, void **, 0xC);
    }
    if (arg1 != NULL) {
        temp_2 = M2C_FIELD(arg1, void **, 4);
        M2C_FIELD(arg1, s32 *, 0) = 0;
        M2C_FIELD(arg1, void **, 8) = NULL;
        M2C_FIELD(arg1, void **, 0xC) = NULL;
        if (temp_2 != NULL) {
            M2C_FIELD(temp_2, s32 *, 0) = 0;
            M2C_FIELD(temp_2, s32 *, 4) = 0;
            M2C_FIELD(temp_2, s32 *, 8) = 0;
            func_00386668(temp_2, 0x1C);
            M2C_FIELD(arg1, void **, 4) = NULL;
        }
        func_00386698(arg1, 0x14);
    }
}
