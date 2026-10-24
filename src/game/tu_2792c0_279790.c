/* Translation unit tu_2792c0 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002797A0();
extern s32 func_00279700();
extern s32 func_00279390();

void func_00279790(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = 0;
    M2C_FIELD(arg0, s32 *, 0x44) = -1;
}

/* Assembly between the functions: func_002797A0 (272 bytes) */

s32 func_002798B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    if (M2C_FIELD(arg0, s32 *, 0x44) < 0) {
        func_002797A0(arg0);
    }
    M2C_FIELD(arg0, s32 *, 0x40) = (s32) (M2C_FIELD(arg0, s32 *, 0x40) + 1);
    func_00279700(arg0, 1);
    func_00279390(arg0, arg1, arg2);
    temp_2 = M2C_FIELD(arg0, s32 *, 0x44) + 1;
    M2C_FIELD(arg0, s32 *, 0x44) = temp_2;
    return temp_2;
}

void func_00279930(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x44) = (s32) (M2C_FIELD(arg0, s32 *, 0x44) - 1);
}

s32 func_00279940(s32 arg0, s32 arg1, s32 arg2) {
    func_00279700(arg0, 0);
    return func_00279390(arg0, arg1, arg2);
}
