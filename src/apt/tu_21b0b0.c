#include "ps2/prelude.h"

extern s32 func_00250198(s32, s32, s32);
extern s32 D_0043DEE0;

void func_0021B0B0(void *arg0) {
    func_00250198(D_0043DEE0, arg0 - 4, M2C_FIELD(arg0, s32 *, -4) + 4);
}
