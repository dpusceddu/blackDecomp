#include "ps2/prelude.h"

void func_001C2760(void *arg0, s32 arg1, f32 fparg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x34);
    if (arg1 >= temp_3) {
        M2C_FIELD(arg0, s32 *, 0x38) = temp_3;
        M2C_FIELD(arg0, s32 *, 0x34) = arg1;
        M2C_FIELD(arg0, f32 *, 0x18) = fparg0;
        M2C_FIELD(arg0, s32 *, 0x24) = 0;
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        M2C_FIELD(arg0, s32 *, 0x20) = 0;
    }
}
