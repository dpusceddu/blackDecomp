/* Translation unit tu_1bec18 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"

extern s32 func_001B0FF8();
extern s32 func_001B1080();
extern s32 func_001D0010(s32);

s32 func_001BEC68(s32 arg0) {
    s32 *temp_3;
    u32 var_3;
    u32 var_4;
    void *temp_2;
    void *temp_5;

    var_3 = 0;
    do {
        temp_2 = (var_3 * 0x130) + arg0;
        M2C_FIELD(temp_2, s8 *, 0x124) = 0;
        var_4 = 0;
        temp_5 = temp_2 + 0xB0;
loop_2:
        temp_3 = temp_5 + (var_4 * 4);
        var_4 = (var_4 + 1) & 0xFFFF;
        *temp_3 = 0;
        if (var_4 < 8U) {
            goto loop_2;
        }
        var_3 = (var_3 + 1) & 0xFFFF;
        M2C_FIELD(temp_5, s32 *, 0x60) = 0;
    } while (var_3 < 0x2CU);
    return 1;
}

s32 func_001BECC8(void) {
    return 1;
}

/* Assembly between the functions: func_001BECD0 (672 bytes), func_001BEF70 (1968 bytes) */

s32 func_001BF720(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    return func_001B0FF8(arg0);
}

/* Assembly between the functions: func_001BF740 (472 bytes), func_001BF918 (1416 bytes) */

s32 func_001BFEA0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    func_001B1080(arg0);
    return 1;
}

/* Assembly between the functions: func_001BFEC8 (8 bytes), func_001BFED0 (272 bytes), func_001BFFE0 (512 bytes), func_001C01E0 (192 bytes), func_001C02A0 (632 bytes), func_001C0518 (192 bytes) */

void func_001C05D8(s32 arg0, s32 arg1) {
    func_001D0010(arg1);
}

void func_001C05F8(void) {

}
