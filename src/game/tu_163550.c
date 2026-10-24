#include "ps2/prelude.h"

extern s32 func_00160EF8();

void func_00163550(void *arg0) {
    func_00160EF8();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}
