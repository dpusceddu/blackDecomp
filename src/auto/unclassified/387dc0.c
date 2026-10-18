#include "auto/prelude.h"

#include "types_ghidra.h"

s32 func_00387DC0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_4 < M2C_FIELD(arg0, s32 *, 0)) {
        temp_2_2 = M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(((temp_4 * 4) + temp_2_2), s32 *, 0) = arg1;
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_4 + 1);
        return temp_2_2;
    }
    temp_2 = M2C_FIELD(arg1, s32 *, 0) & ~4;
    M2C_FIELD(arg1, s32 *, 0) = temp_2;
    return temp_2;
}
