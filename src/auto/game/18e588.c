#include "auto/prelude.h"

extern s32 func_0018DDE8();

s32 func_0018E588(void) {
    return 1;
}

void func_0018E590(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 4);
    func_0018DDE8(temp_4 + 0xC94, M2C_FIELD(temp_4, s32 *, 0x754));
}
