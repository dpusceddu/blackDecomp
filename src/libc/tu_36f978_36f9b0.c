/* Translation unit libstdcxx_typeinfo/tu_36f978 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 D_003D881C;
extern void ** func_00292088();
extern s32 func_0035E828();
extern M2C_UNK D_0040BEA0;
extern s32 func_00107D48();
extern M2C_UNK D_0040BE88;

s32 func_0036F9B0(s32 arg0) {
    s32 temp_2;

    temp_2 = D_003D881C;
    D_003D881C = arg0;
    return temp_2;
}

/* Assembly between the functions: func_0036F9C0 (64 bytes) */

void * func_0036FA00(void) {
    return *func_00292088();
}

void * func_0036FA20(void) {
    void *temp_3;

    temp_3 = *func_00292088();
    M2C_FIELD(temp_3, s32 *, 0x14) = 1;
    M2C_FIELD(temp_3, s64 *, 0x20) = (s64) (M2C_FIELD(temp_3, s64 *, 0x20) + 1);
    return temp_3;
}

/* Assembly between the functions: func_0036FA58 (40 bytes) */

void func_0036FA80(void) {
    func_0035E828();
}

/* Assembly between the functions: func_0036FAA0 (112 bytes), func_0036FB10 (144 bytes), func_0036FBA0 (200 bytes), func_0036FC68 (48 bytes), func_0036FC98 (752 bytes) */

s32 func_0036FF88(void **arg0) {
    return *M2C_FIELD(*arg0, s32 *(**)(), 4)();
}

s32 func_0036FFB0(s32 arg0, s32 arg1) {
    M2C_UNK *var_2;

    var_2 = &D_0040BEA0;
    M2C_FIELD(arg0, u32 *, 0) = &D_0040BEA0;
    if (arg1 & 1) {
        var_2 = func_00107D48(arg0);
    }
    return (s32) var_2;
}

M2C_UNK ** func_0036FFE0(M2C_UNK **arg0) {
    *arg0 = &D_0040BE88;
    return arg0;
}
