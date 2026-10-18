#include "auto/prelude.h"

extern s32 func_0035C544();

void func_003500A8(s32 arg0, s32 arg1) {
    if (arg0 != arg1) {
        M2C_FIELD(arg0, s32 *, 0x118) = (s32) M2C_FIELD(arg1, s32 *, 0x118);
        func_0035C544(arg0, arg1, M2C_FIELD(arg1, s32 *, 0x118) * 4);
    }
}
