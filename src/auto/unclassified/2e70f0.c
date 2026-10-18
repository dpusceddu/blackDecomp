#include "auto/prelude.h"

extern s32 func_002E5AE8();
extern M2C_UNK D_003E9A98;
extern M2C_UNK D_003E9AF0;

s32 func_002E70F0(s32 arg0, s32 arg1) {
    func_002E5AE8(arg0, M2C_FIELD(arg1, s32 *, 0xC), arg1 + 0x10, 0);
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003E9A98;
    M2C_FIELD(arg0, M2C_UNK **, 0x28) = &D_003E9AF0;
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    return arg0;
}
