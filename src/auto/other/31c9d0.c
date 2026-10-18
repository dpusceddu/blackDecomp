#include "auto/prelude.h"

s32 func_0031C9D0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x9C) & 4) {
        return M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0xA4) * 0x18) + M2C_FIELD(arg0, s32 *, 0x50)), s32 *, 0x14) == 0;
    }
    return 0;
}
