#include "ps2/prelude.h"

extern s32 func_001F1C10();

s32 func_001F1EE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    M2C_FIELD(arg0, s32 *, 0x60) = 0;
    return func_001F1C10(arg0, arg1, arg2, arg3, (s32) (s8) arg4, arg5, arg6);
}
