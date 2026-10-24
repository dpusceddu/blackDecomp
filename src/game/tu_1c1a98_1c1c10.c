#include "ps2/prelude.h"

extern s32 func_001D4030();

void func_001C1C10(void *arg0) {
    func_001D4030();
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
}
