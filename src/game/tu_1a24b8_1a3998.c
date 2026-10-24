#include "ps2/prelude.h"

extern s32 func_001A2590();
extern s8 func_00178F18(s32);
extern s32 func_001A2620();

s32 func_001A3998(void) {
    return 1;
}

void func_001A39A0(void *arg0) {
    func_001A2590();
    M2C_FIELD(arg0, s8 *, 0x82) = func_00178F18(func_001A2620(arg0));
}
