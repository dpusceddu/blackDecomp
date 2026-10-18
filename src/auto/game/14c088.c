#include "auto/prelude.h"

void func_0014C088(void *arg0, s32 arg1) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x124);
    if (temp_3 != 3) {
        if ((u32) (arg1 - 2) < 2U) {
            M2C_FIELD(arg0, s32 *, 0x124) = 2;
            return;
        }
        if ((temp_3 == 0) && (arg1 == 1)) {
            M2C_FIELD(arg0, s32 *, 0x124) = arg1;
        }
    }
}
