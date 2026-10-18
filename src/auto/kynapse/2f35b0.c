#include "auto/prelude.h"

extern s32 func_00390F40();
extern M2C_UNK D_003EDD88;

s32 func_002F35B0(s32 arg0, s32 arg1, s32 arg2) {
    func_00390F40(arg0, arg1, arg2, 0, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EDD88;
    return arg0;
}
