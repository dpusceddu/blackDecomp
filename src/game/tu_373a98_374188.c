/* Translation unit tu_373a98 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00377628(s32);
extern s32 func_00311B50();
extern s32 func_00377840();
extern s32 func_00322C70();

void func_00374188(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        func_00377628(arg0 + 0x84);
    }
}

/* Assembly between the functions: func_003741A8 (416 bytes) */

s32 func_00374348(s32 arg0, s32 arg1, s32 arg2) {
    func_00374188(arg0, 1);
    func_00311B50(M2C_FIELD(arg0, s32 *, 0x80));
    func_00377840(arg0 + 0x84);
    return func_00322C70(arg0, arg1, arg2);
}
