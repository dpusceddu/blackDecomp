/* Translation unit renderware_core/tu_2a8f78 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 (*D_004494D4)();
extern s32 func_002AC6E8(s32);
extern s32 func_002A8688();
extern s32 func_002A7DD0();
extern s32 func_002A8DA0();
extern s32 func_002A8860();
extern void * func_002D0910();
extern s32 func_002CFAC0();
extern M2C_UNK D_003C3210;

void func_002A90C8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x18)();
}

void func_002A90E8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x1C)();
}

s32 func_002A9108(s32 arg0) {
    return (D_004494D4() == 0) ? 0 : arg0;
}

void * func_002A9140(void *arg0) {
    return (func_002AC6E8(M2C_FIELD(arg0, s32 *, 0x60)) == 0) ? NULL : arg0;
}

/* Assembly between the functions: func_002A9170 (8 bytes), func_002A9178 (96 bytes), func_002A91D8 (104 bytes), func_002A9240 (208 bytes), func_002A9310 (208 bytes), func_002A93E0 (72 bytes), func_002A9428 (8 bytes), func_002A9430 (104 bytes), func_002A9498 (128 bytes) */

void * func_002A9518(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x14) == 1) {
        func_002A8688();
        func_002A7DD0(arg0);
    } else {
        func_002A8DA0(arg0);
        func_002A8860(arg0);
    }
    func_002D0910(arg0 + 0x10C, arg0 + 0x124, 8);
    return arg0;
}

/* Assembly between the functions: func_002A9588 (88 bytes), func_002A95E0 (96 bytes), func_002A9640 (496 bytes), func_002A9830 (8 bytes), func_002A9838 (112 bytes), func_002A98A8 (104 bytes), func_002A9910 (200 bytes), func_002A99D8 (272 bytes), func_002A9AE8 (136 bytes), func_002A9B70 (320 bytes), func_002A9CB0 (8 bytes), func_002A9CB8 (312 bytes) */

void func_002A9DF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_002CFAC0(&D_003C3210, arg0, arg1, arg2, arg3, 0);
}
