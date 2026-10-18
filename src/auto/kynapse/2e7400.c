#include "auto/prelude.h"

extern s32 func_0038E438();
extern M2C_UNK D_003EA7A8;
extern s32 func_0038E108();
extern M2C_UNK D_003EA778;

s32 func_002E7400(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0038E438(arg0, arg1, arg2, arg3, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EA7A8;
    return arg0;
}

s32 func_002E7440(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0038E108(arg0, arg1, arg2, arg3, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EA778;
    return arg0;
}
