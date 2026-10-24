#include "ps2/prelude.h"

extern s32 func_0017E5A8(s32);

s32 func_00182510(void *arg0) {
    func_0017E5A8(M2C_FIELD(arg0, s32 *, 0x310) + 0x650);
    M2C_FIELD(arg0, s8 *, 0x37) = 1;
    return 1;
}
