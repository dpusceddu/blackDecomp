#include "auto/prelude.h"

extern s32 func_0038B6B0();
extern M2C_UNK D_003E6D40;

s32 func_002DFDC8(s32 arg0, s32 arg1, s32 arg2) {
    func_0038B6B0(arg0, arg1, arg2, 0, 0, 0);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003E6D40;
    return arg0;
}
