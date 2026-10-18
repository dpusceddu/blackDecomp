#include "auto/prelude.h"

extern s32 func_00332768(M2C_UNK, M2C_UNK);

void * func_003328B0(void **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    void *temp_4;

    temp_4 = *arg0;
    if (temp_4 != NULL) {
        M2C_FIELD(temp_4, s32 *, 0) = 0;
        M2C_FIELD(temp_4, s32 *, 4) = 0;
        M2C_FIELD(temp_4, s32 *, 8) = 0;
        M2C_FIELD(temp_4, s32 *, 0xC) = 0;
        M2C_FIELD(temp_4, s32 *, 0x10) = 0;
    }
    M2C_FIELD(temp_4, s32 *, 0) = arg1;
    M2C_FIELD(temp_4, s32 *, 4) = arg2;
    M2C_FIELD(temp_4, s32 *, 0xC) = arg3;
    M2C_FIELD(temp_4, s32 *, 8) = arg4;
    return temp_4;
}

void func_003328E8(void) {
    func_00332768(1, 0xFFFF);
}

void func_00332908(void) {
    func_00332768(0, 0xFFFF);
}
