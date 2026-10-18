#include "auto/prelude.h"

extern s32 func_001F1C08();

void func_001F44C0(void *arg0) {
    func_001F1C08();
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
}
