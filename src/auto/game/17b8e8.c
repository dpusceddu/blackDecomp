#include "auto/prelude.h"

extern s32 func_00174228();
extern s32 func_001742B8();

void func_0017B8E8(void) {
    func_00174228();
}

void func_0017B908(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, s32 *, 0xC) == arg1) {
        M2C_FIELD(arg0, s32 *, 0xC) = 0;
    }
    func_001742B8();
}
