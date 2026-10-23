#include "auto/prelude.h"

s32 func_003535E0(void *arg0, s32 arg1, u32 arg2, s32 arg3) {
    u32 temp_3;

    temp_3 = M2C_FIELD(arg0, u32 *, 0x474);
    if (temp_3 != 0) {
        if (arg1 != 0) {
            return (u32) (arg2 + arg3) >= temp_3;
        }
        return arg2 < temp_3;
    }
    return 1;
}
