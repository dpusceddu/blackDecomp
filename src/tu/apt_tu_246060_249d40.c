/* Translation unit apt/tu_246060 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_00249F28();
extern s32 (*D_0043DAE8)();
extern s32 D_0043DF40;

void func_00249D40(void *arg0) {
    s32 temp_2;
    void *temp_3;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x3B8);
    M2C_FIELD(arg0, s32 *, 0x3B8) = (s32) (temp_2 + 1);
    temp_3 = arg0 + ((temp_2 << 5) + 0x20);
    M2C_FIELD(temp_3, s128 *, 0) = (s128) M2C_FIELD(arg0, s128 *, 0);
    M2C_FIELD(temp_3, s128 *, 0x10) = (s128) M2C_FIELD(arg0, s128 *, 0x10);
}

void func_00249D70(void *arg0) {
    s32 temp_2;
    void *temp_5;

    temp_2 = M2C_FIELD(arg0, s32 *, 0x3B8) - 1;
    M2C_FIELD(arg0, s32 *, 0x3B8) = temp_2;
    temp_5 = arg0 + ((temp_2 << 5) + 0x20);
    M2C_FIELD(arg0, s128 *, 0) = (s128) M2C_FIELD(temp_5, s128 *, 0);
    M2C_FIELD(arg0, s128 *, 0x10) = (s128) M2C_FIELD(temp_5, s128 *, 0x10);
}

/* Assembly between the functions: func_00249DA0 (200 bytes), func_00249E68 (80 bytes), func_00249EB8 (112 bytes), func_00249F28 (216 bytes) */

s32 func_0024A000(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = arg0 + 0x220;
    func_00249F28(temp_16, arg1, temp_16);
    return D_0043DAE8(temp_16);
}

/* Assembly between the functions: func_0024A040 (328 bytes), func_0024A188 (320 bytes), func_0024A2C8 (144 bytes), func_0024A358 (8 bytes), func_0024A360 (368 bytes), func_0024A4D0 (96 bytes) */

s32 func_0024A530(void) {
    return D_0043DF40;
}
