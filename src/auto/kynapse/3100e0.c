#include "auto/prelude.h"

extern s32 func_0030F678();

s32 func_003100E0(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0x49) = 0;
    M2C_FIELD(arg0, s8 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s8 *, 0x50) = 1;
    func_0030F678(arg0);
    return M2C_FIELD(arg0, s32 *, 0x2C);
}
