#include "ps2/prelude.h"

extern s32 func_00319E28(s32, s32);

void func_00284990(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 4) = arg1;
    M2C_FIELD(arg0, s8 *, 0x2C) = 0;
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    func_00319E28(M2C_FIELD(arg0, s32 *, 0x34), M2C_FIELD(arg1, s32 *, 0x18));
}
