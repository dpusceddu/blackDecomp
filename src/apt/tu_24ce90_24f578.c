/* Translation unit apt/tu_24ce90 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_00249958(s32, s32);
extern s32 func_002487E0(s32);
extern s32 func_0024B3B0();

void func_0024F578(u32 *arg0) {
    u32 temp_6;
    u32 var_4;

    temp_6 = *arg0;
    var_4 = ((temp_6 >> 6) & 0xFFF) + 1;
    if (var_4 >= 0x1000U) {
        var_4 = 0xFFF;
        *arg0 = (temp_6 & 0xFEFFFFFF) | 0x01000000;
    }
    *arg0 = (*arg0 & 0xFFFC003F) | ((var_4 & 0xFFF) << 6);
}

/* Assembly between the functions: func_0024F5D8 (392 bytes) */

s32 func_0024F760(s32 arg0) {
    return arg0 + 8;
}

s32 func_0024F768(void) {
    return 1;
}

void func_0024F770(s32 arg0) {
    func_00249958(arg0 + 8, arg0);
}

void func_0024F790(void *arg0) {
    func_002487E0(arg0 + 8);
}

void func_0024F7B0(void) {
    func_0024B3B0();
}
