#include "auto/prelude.h"

#include "types_ghidra.h"

s32 func_00328520(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg2, s32 *, 0) = (s32) (M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 0x1C) & 1);
    return arg0;
}
