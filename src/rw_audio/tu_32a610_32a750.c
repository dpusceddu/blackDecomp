/* Translation unit rwa_ee/tu_32a610 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

u32 func_0032A750(s32 arg0, u32 arg1, s32 arg2, void *arg3) {
    return M2C_FIELD(M2C_FIELD(arg3, void **, 0x50), u32 (**)(void *, s32, s32), 0x30)(arg3, arg0, arg1 * arg2) / arg1;
}

u32 func_0032A7A0(s32 arg0, u32 arg1, s32 arg2, void *arg3) {
    return M2C_FIELD(M2C_FIELD(arg3, void **, 0x50), u32 (**)(void *, s32, s32), 0x34)(arg3, arg0, arg1 * arg2) / arg1;
}

/* Assembly between the functions: func_0032A7F0 (216 bytes) */

void func_0032A8C8(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x50), M2C_UNK (**)(), 0x44)();
}
