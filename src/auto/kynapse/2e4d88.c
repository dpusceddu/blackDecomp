#include "auto/prelude.h"

extern s32 func_0038CF20();
extern M2C_UNK D_003E9110;
extern s32 func_0038D0B0();
extern M2C_UNK D_003E90F8;

s32 func_002E4D88(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0038CF20(arg0, arg1, arg2, arg3, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E9110;
    return arg0;
}

s32 func_002E4DC8(s32 arg0, s32 arg1, s32 arg2) {
    func_0038D0B0(arg0, arg1, arg2, 0, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E90F8;
    return arg0;
}
