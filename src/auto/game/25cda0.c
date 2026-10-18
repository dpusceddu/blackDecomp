#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_0025C910();

s32 func_0025CDA0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_2;

    temp_2 = func_0025C910(arg0, arg2);
    M2C_FIELD(arg0, s32 *, 0x8B04) = temp_2;
    M2C_FIELD(arg1, s32 *, 0) = temp_2;
    return ~M2C_FIELD(arg0, s32 *, 0x8B04) != 0;
}
