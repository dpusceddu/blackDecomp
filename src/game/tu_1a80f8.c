#include "auto/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 * func_00107D20(s32);

s32 * func_001A80F8(void *arg0) {
    s32 *temp_2;
    s32 *temp_2_2;
    s32 *var_2;
    s32 var_3;

    var_3 = 7;
    M2C_FIELD(arg0, s32 *, 8) = 0;
    var_2 = (s32 *) (((s8 *) arg0) + 0x28);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    M2C_FIELD(arg0, s8 *, 0x54) = 0;
    do {
        *var_2 = 0;
        var_3 -= 1;
        var_2 = (s32 *) (((s8 *) var_2) + -4);
    } while (var_3 >= 0);
    M2C_FIELD(arg0, s32 *, 0x2C) = 0;
    temp_2_2 = func_00107D20(0xB0);
    M2C_FIELD(arg0, s32 *, 0x58) = 0;
    M2C_FIELD(arg0, s32 **, 0x30) = temp_2_2;
    temp_2 = func_00107D20(0x4650);
    M2C_FIELD(arg0, s32 **, 4) = temp_2;
    return temp_2;
}
