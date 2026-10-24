#include "ps2/prelude.h"

extern s32 func_00284298(s32);

void func_001E36A0(void *arg0) {
    func_00284298(M2C_FIELD(arg0, s32 *, 0x28));
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0x28) = 0;
}
