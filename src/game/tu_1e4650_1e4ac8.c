/* Translation unit tu_1e4650 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

void func_001E4AC8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x28) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = 3;
}

/* Assembly between the functions: func_001E4AD8 (96 bytes) */

s32 func_001E4B38(void *arg0) {
    s32 temp_3;
    s32 var_4;

    temp_3 = M2C_FIELD(arg0, s32 *, 4);
    var_4 = 0;
    if ((temp_3 == 1) || (temp_3 == 3) || (temp_3 == 2) || (temp_3 == 4)) {
        var_4 = 1;
    }
    return var_4;
}
