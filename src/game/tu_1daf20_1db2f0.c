/* Translation unit tu_1daf20 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_001DD6C0();

void func_001DB2F0(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x1C) = fparg0;
}

/* Assembly between the functions: func_001DB2F8 (424 bytes) */

s32 func_001DB4A0(s32 arg0) {
    s32 temp_3;
    s32 var_2;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x28);
    var_2 = temp_3 < 7;
    if ((temp_3 >= 0) && (var_2 == 0)) {
        var_2 = temp_3 < 0xA;
        if (var_2 != 0) {
            func_001DD6C0(M2C_FIELD(arg0, s32 *, 0));
            var_2 = 6;
            M2C_FIELD(arg0, s32 *, 0x28) = 6;
        }
    }
    return var_2;
}

/* Assembly between the functions: func_001DB4F0 (256 bytes), func_001DB5F0 (1040 bytes), func_001DBA00 (952 bytes), func_001DBDB8 (288 bytes), func_001DBED8 (96 bytes), func_001DBF38 (200 bytes), func_001DC000 (56 bytes), func_001DC038 (360 bytes), func_001DC1A0 (216 bytes), func_001DC278 (72 bytes), func_001DC2C0 (392 bytes), func_001DC448 (80 bytes) ... */

void func_001DD4C8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x4C) = arg1;
}
