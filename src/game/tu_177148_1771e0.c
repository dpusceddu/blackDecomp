/* Translation unit tu_177148 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00177800();
extern s32 func_001779D0();

s32 func_001771E0(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x978) = 0;
    return 1;
}

/* Assembly between the functions: func_001771F0 (72 bytes) */

void func_00177238(void) {
    func_00177800();
}

/* Assembly between the functions: func_00177258 (248 bytes), func_00177350 (288 bytes), func_00177470 (560 bytes), func_001776A0 (176 bytes), func_00177750 (48 bytes), func_00177780 (80 bytes), func_001777D0 (48 bytes), func_00177800 (168 bytes), func_001778A8 (136 bytes), func_00177930 (88 bytes) */

void * func_00177988(void *arg0) {
    if (func_001779D0() != 0) {
        return NULL;
    }
    return arg0 + (M2C_FIELD(arg0, s32 *, 0x960) * 8);
}

s32 func_001779C0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x968) == 0x12C;
}

s32 func_001779D0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x968) == 0;
}

s32 func_001779E0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x968);
}
