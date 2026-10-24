#include "ps2/prelude.h"

extern s32 func_001829A8();
extern s32 func_00182550();
extern s32 func_00182318();

void func_001825B0(void *arg0) {
    if (func_001829A8(arg0) != 0) {
        func_00182550(arg0, 0);
    } else {
        func_00182550(arg0, M2C_FIELD(arg0, s32 *, 0x30));
    }
    func_00182318(arg0, 0);
}
