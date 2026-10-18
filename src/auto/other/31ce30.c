#include "auto/prelude.h"

#include "types_ghidra.h"

s32 func_0031CE30(s32 arg0, s32 arg1) {
    *M2C_FIELD(arg0, s32 **, 0x90) = (M2C_FIELD(arg1, s32 *, 0) != 0) ? 2 : 1;
    return arg0;
}
