/* Translation unit libipu_libmpeg/tu_292f08 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

u8 * func_00292F08(u8 *arg0, s32 *arg1) {
    s32 var_6;
    s32 var_7;
    u8 *var_4;
    u8 temp_3;
    u8 temp_3_2;

    temp_3 = *arg0;
    var_7 = 0;
    var_4 = arg0 + 1;
    var_6 = temp_3 & 0x7F;
    if (temp_3 & 0x80) {
        do {
            temp_3_2 = *var_4;
            var_7 += 7;
            var_4 += 1;
            var_6 |= (temp_3_2 & 0x7F) << var_7;
        } while (temp_3_2 & 0x80);
    }
    *arg1 = var_6;
    return var_4;
}

u8 * func_00292F50(u8 *arg0, s32 *arg1) {
    s32 var_8;
    u32 var_7;
    u8 *var_4;
    u8 temp_6;

    var_4 = arg0;
    var_7 = 0;
    var_8 = 0;
    do {
        temp_6 = *var_4;
        var_4 += 1;
        var_8 |= (temp_6 & 0x7F) << var_7;
        var_7 += 7;
    } while (temp_6 & 0x80);
    if ((var_7 < 0x20U) && (temp_6 & 0x40)) {
        var_8 |= -1 << var_7;
    }
    *arg1 = var_8;
    return var_4;
}

/* Assembly between the functions: func_00292FA0 (256 bytes), func_002930A0 (616 bytes), func_00293308 (72 bytes) */

s32 func_00293350(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_4;
    s32 var_8;
    u32 temp_3;
    u32 temp_4_2;
    u32 var_10;
    u32 var_9;
    void *var_2;

    var_8 = arg0;
    var_2 = M2C_FIELD(var_8, u32 *, 0);
    var_9 = M2C_FIELD(arg2, u32 *, 0);
    var_10 = M2C_FIELD(arg3, u32 *, 0);
    if (var_2 != NULL) {
        do {
            if ((M2C_FIELD(var_8, s32 *, 4) != 0) && (M2C_FIELD(var_8, u32 *, 8) != 0)) {
                temp_4 = M2C_FIELD(arg1, s32 *, 4);
                M2C_FIELD(((temp_4 * 4) + M2C_FIELD(arg1, s32 *, 0)), s32 *, 0) = var_8;
                M2C_FIELD(arg1, s32 *, 4) = (s32) (temp_4 + 1);
                temp_3 = M2C_FIELD(var_8, u32 *, 8);
                temp_4_2 = temp_3 + M2C_FIELD(var_8, s32 *, 0xC);
                var_9 = (temp_3 < var_9) ? temp_3 : var_9;
                var_10 = (var_10 < temp_4_2) ? temp_4_2 : var_10;
            }
            var_2 = var_8 + M2C_FIELD(var_8, s32 *, 0);
            var_8 = (s32) (var_2 + 4);
        } while (M2C_FIELD(var_2, s32 *, 4) != 0);
    }
    M2C_FIELD(arg2, u32 *, 0) = var_9;
    M2C_FIELD(arg3, u32 *, 0) = var_10;
    return (s32) var_2;
}
