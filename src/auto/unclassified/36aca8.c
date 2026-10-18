#include "auto/prelude.h"

extern s32 func_0036A6A0();

s32 func_0036ACA8(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    return (func_0036A6A0(0x80000008, arg3, 0x40, M2C_FIELD(arg3, s32 *, 0x24), M2C_FIELD(arg3, s32 *, 0x28), M2C_FIELD(arg3, s32 *, 0x2C)) != 0) ? 0 : 0x800;
}
