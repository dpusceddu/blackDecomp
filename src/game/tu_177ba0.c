#include "ps2/prelude.h"

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES

s32 func_00177BA0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_2;
    s32 temp_5;
    s32 var_2;
    s32 var_2_2;

    temp_5 = 1 << arg1;
    if (arg2 != 0) {
        var_2 = M2C_FIELD(arg0, s32 *, 0x18) | temp_5;
    } else {
        var_2 = M2C_FIELD(arg0, s32 *, 0x18) & ~temp_5;
    }
    M2C_FIELD(arg0, s32 *, 0x18) = var_2;
    if (arg3 != 0) {
        var_2_2 = M2C_FIELD(arg0, s32 *, 0x14) | temp_5;
    } else {
        var_2_2 = M2C_FIELD(arg0, s32 *, 0x14) & ~temp_5;
    }
    M2C_FIELD(arg0, s32 *, 0x14) = var_2_2;
    temp_2 = M2C_FIELD(arg0, s32 *, 0x20) | temp_5;
    M2C_FIELD(arg0, s32 *, 0x20) = temp_2;
    M2C_FIELD(arg0, s32 *, 0x1C) = (s32) (M2C_FIELD(arg0, s32 *, 0x1C) | temp_5);
    return temp_2;
}
