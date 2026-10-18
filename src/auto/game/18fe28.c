#include "auto/prelude.h"

extern s32 func_00180A00(s32);

u8 func_0018FE28(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x40);
}

void func_0018FE30(void *arg0) {
    func_00180A00(M2C_FIELD(arg0, s32 *, 4) + 0xB30);
}

s32 func_0018FE50(void) {
    return 1;
}
