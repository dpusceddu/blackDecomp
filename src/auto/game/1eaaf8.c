#include "auto/prelude.h"

extern s32 func_0035C6EC();

s32 func_001EAAF8(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = -1;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    return func_0035C6EC(arg0, 0, 0x40);
}

s32 func_001EAB30(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x40) = arg2;
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
    func_0035C6EC(arg0, 0, 0x40);
    return 1;
}
