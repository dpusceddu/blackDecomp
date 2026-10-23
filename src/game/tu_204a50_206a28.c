#include "auto/prelude.h"

extern s32 func_00204FF0();

void func_00206A28(void *arg0) {
    func_00204FF0();
    M2C_FIELD(arg0, s32 *, 0x1C) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = 0;
}
