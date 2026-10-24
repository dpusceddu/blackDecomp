#include "ps2/prelude.h"

extern s32 func_00160ED8();

s32 func_00163C28(void *arg0) {
    func_00160ED8();
    M2C_FIELD(arg0, s32 *, 0x24) = 4;
    return 1;
}
