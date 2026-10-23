/* Translation unit rwa_ee/tu_323ed0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 D_00458DC0;
extern s32 func_0036CD08(M2C_UNK, s32, M2C_UNK);
extern void func_00324E38(s32 arg0, s32 arg1);

s32 func_00324650(void) {
    return D_00458DC0;
}

/* Assembly between the functions: func_00324660 (128 bytes), func_003246E0 (192 bytes), func_003247A0 (264 bytes), func_003248A8 (88 bytes), func_00324900 (72 bytes), func_00324948 (32 bytes), func_00324968 (40 bytes), func_00324990 (88 bytes), func_003249E8 (160 bytes), func_00324A88 (280 bytes), func_00324BA0 (272 bytes), func_00324CB0 (232 bytes) ... */

s32 func_00324DE8(s32 arg0) {
    s32 temp_2;

    temp_2 = func_0036CD08(0, arg0, 0);
    func_00324E38(temp_2, arg0);
    return temp_2;
}
