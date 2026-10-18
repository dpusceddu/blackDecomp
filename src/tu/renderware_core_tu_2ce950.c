/* Translation unit renderware_core/tu_2ce950 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern M2C_UNK D_0040A991;

s32 func_002CF5C0(void) {
    return 1;
}

s32 func_002CF5C8(void) {
    return 1;
}

void func_002CF5D0(void) {

}

void func_002CF5D8(void) {

}

void * func_002CFE90(void *arg0, s32 arg1) {
    void *var_16;

    var_16 = M2C_FIELD(arg0, void **, 0x14);
    if (var_16 != NULL) {
        do {
            M2C_FIELD(var_16, M2C_UNK (**)(s32, s32, s32), 0x24)(arg1, M2C_FIELD(var_16, s32 *, 0), M2C_FIELD(var_16, s32 *, 4));
            var_16 = M2C_FIELD(var_16, void **, 0x34);
        } while (var_16 != NULL);
    }
    return arg0;
}

s32 func_002CFF40(s32 arg0) {
    return arg0;
}

s32 func_002CFF48(s32 arg0) {
    return arg0;
}

s32 func_002CFF50(s32 arg0) {
    return arg0;
}

s32 func_002CFFB0(void) {
    return 1;
}

void func_002D0678(void) {

}

s8 * func_002D07C8(s8 *arg0) {
    s8 *var_3;
    s8 temp_5;

    if (arg0 != NULL) {
        var_3 = arg0;
        if (*arg0 != 0) {
            do {
                temp_5 = *var_3;
                if ((u32) (temp_5 - 0x61) < 0x1AU) {
                    *var_3 = temp_5 - 0x20;
                }
                var_3 += 1;
            } while (*var_3 != 0);
        }
    }
    return arg0;
}

s8 * func_002D0810(s8 *arg0) {
    s8 *var_3;
    s8 temp_5;

    if (arg0 != NULL) {
        var_3 = arg0;
        if (*arg0 != 0) {
            do {
                temp_5 = *var_3;
                if ((u32) (temp_5 - 0x41) < 0x1AU) {
                    *var_3 = temp_5 + 0x20;
                }
                var_3 += 1;
            } while (*var_3 != 0);
        }
    }
    return arg0;
}

s8 * func_002D0890(s8 *arg0, s8 arg1) {
    s8 *var_4;
    s8 *var_6;
    s8 *var_7;
    s8 temp_3;

    var_4 = arg0;
    var_7 = NULL;
    var_6 = var_4;
    do {
        temp_3 = *var_6;
        var_6 += 1;
        var_7 = ((temp_3 ^ arg1) == 0) ? var_4 : var_7;
        var_4 += 1;
    } while (temp_3 != 0);
    return var_7;
}

s32 func_002D08C8(void *arg0) {
    s32 var_5;
    s8 temp_3;

    var_5 = 0;
    if ((arg0 != NULL) && ((temp_3 = M2C_FIELD(arg0, s8 *, 0), (temp_3 == 0x5C)) || ((M2C_FIELD((temp_3 + ((s32) &D_0040A991)), u8 *, 0) & 3) && (M2C_FIELD(arg0, s8 *, 1) == 0x3A)))) {
        var_5 = 1;
    }
    return var_5;
}
