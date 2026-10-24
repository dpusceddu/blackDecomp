#include "ps2/prelude.h"

extern s32 func_0017B310();

void func_0017B358(void *arg0) {
    func_0017B310();
    M2C_FIELD(arg0, s32 *, 0x24) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}
