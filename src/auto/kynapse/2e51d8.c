#include "auto/prelude.h"

extern s32 func_0038D4C0();
extern M2C_UNK D_003E9678;

s32 func_002E51D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0038D4C0(arg0, arg1, arg2, arg3, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E9678;
    return arg0;
}
