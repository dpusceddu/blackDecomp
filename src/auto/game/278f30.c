#include "auto/prelude.h"

#include "types_ghidra.h"

s32 func_00278F30(s32 arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0) + arg0;
    M2C_FIELD(arg0, s32 *, 0) = temp_2;
    return temp_2;
}
