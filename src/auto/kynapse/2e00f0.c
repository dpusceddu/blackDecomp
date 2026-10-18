#include "auto/prelude.h"

extern s32 func_0038BBB0();
extern M2C_UNK D_003E75A0;

s32 func_002E00F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_0038BBB0(arg0, arg1, arg2, arg3, arg4 & 0xFF, arg5 & 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E75A0;
    return arg0;
}
