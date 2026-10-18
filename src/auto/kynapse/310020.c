#include "auto/prelude.h"

extern s32 func_0030F678();

s32 func_00310020(s32 arg0) {
    M2C_FIELD(arg0, s8 *, 0x49) = 0;
    M2C_FIELD(arg0, s8 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
    M2C_FIELD(arg0, s8 *, 0x50) = 1;
    func_0030F678(arg0);
    return M2C_FIELD(arg0, s32 *, 0x20);
}
