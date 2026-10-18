#include "auto/prelude.h"

extern s32 func_00107D20();
extern s32 func_001ADDF8();

void func_001ADD78(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_17;
    s32 temp_2;

    temp_17 = arg3 * 4;
    M2C_FIELD(arg0, s32 *, 0) = func_00107D20(temp_17);
    temp_2 = func_00107D20(temp_17);
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = arg2;
    M2C_FIELD(arg0, s32 *, 0x10) = arg3;
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    func_001ADDF8(arg0);
}
