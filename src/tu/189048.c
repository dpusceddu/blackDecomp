#include "auto/prelude.h"

extern s128 * func_00178D30();
extern s32 func_00179258();
extern s32 D_0040F4D4;
extern s32 func_00189178();

s32 func_00189048(s32 arg0) {
    return func_00189070(arg0, (M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0);
}

s128 func_00189070(s32 arg0, s32 *arg1) {
    return *func_00178D30(func_00179258(D_0040F4D4 + 0xFA8, *arg1));
}

s32 func_001890A8(s32 arg0) {
    return func_00189178(arg0, (M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0);
}
