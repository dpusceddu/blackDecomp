#include "auto/prelude.h"

extern s32 func_001092F8();

void func_001ABEB8(s32 arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x6C) = func_001092F8();
}
