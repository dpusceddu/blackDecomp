#include "ps2/prelude.h"

extern s32 func_00324FA0();
extern s32 func_00315FF0();

s32 func_0031D520(void) {
    return 0x11940000;
}

void func_0031D528(void *arg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x54) & 0x40)) {
        func_00324FA0();
        return;
    }
    func_00315FF0();
}
