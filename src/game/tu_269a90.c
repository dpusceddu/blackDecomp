#include "ps2/prelude.h"

extern s32 func_0036BFB0(s32);

void func_00269A90(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    func_0036BFB0(M2C_FIELD(arg0, s32 *, 0x30));
}
