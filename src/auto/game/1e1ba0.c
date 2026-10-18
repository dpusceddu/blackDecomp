#include "auto/prelude.h"

extern s32 func_0035C6EC(s32, M2C_UNK, M2C_UNK);

s32 func_001E1BA0(void *arg0) {
    func_0035C6EC(arg0 + 0x20, 0, 0x28);
    M2C_FIELD(arg0, s32 *, 0x5C) = 7;
    return 1;
}
