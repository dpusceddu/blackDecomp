#include "auto/prelude.h"

extern s32 func_001F0C98();

void func_001D7100(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 temp_11;

    temp_11 = M2C_FIELD(arg7, s32 *, 0x1BE0);
    if (temp_11 != 0) {
        func_001F0C98(arg0, arg1, arg2, arg3, arg4, arg5, arg6, temp_11 + 0x1D0);
    }
}
