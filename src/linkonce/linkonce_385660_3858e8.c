#include "ps2/prelude.h"

s32 func_003858E8(void *arg0) {
    return *M2C_FIELD(arg0, s32 **, 0x30);
}

s32 func_003858F8(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 4);
}

s32 func_00385908(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30) + 0x18;
}

s32 func_00385918(void *arg0) {
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 0xC);
}
