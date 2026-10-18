#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00189740();
extern s32 func_00189B90();

s32 func_00189700(s32 arg0, s32 arg1) {
    return func_00189740(arg0, arg1, 1);
}

s32 func_00189720(s32 arg0, s32 arg1) {
    return func_00189B90(arg0, M2C_FIELD(arg1, s32 *, 0x380));
}
