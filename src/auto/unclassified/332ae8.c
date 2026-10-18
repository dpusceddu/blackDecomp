#include "auto/prelude.h"

void * func_00332AE8(void **arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_4;

    temp_4 = *arg0;
    if (temp_4 != NULL) {
        M2C_FIELD(temp_4, s32 *, 0) = 0;
        M2C_FIELD(temp_4, s32 *, 0x54) = 0;
        M2C_FIELD(temp_4, s32 *, 0x58) = 0;
        M2C_FIELD(temp_4, s32 *, 0x5C) = 0;
    }
    M2C_FIELD(temp_4, s32 *, 0) = arg2;
    M2C_FIELD(temp_4, s32 *, 0x54) = arg1;
    M2C_FIELD(temp_4, s32 *, 0x5C) = arg3;
    M2C_FIELD(temp_4, s32 *, 0x50) = 0;
    return temp_4;
}
