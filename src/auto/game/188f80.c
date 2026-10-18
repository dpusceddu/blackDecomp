#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00179258();
extern s32 D_0040F4D4;

s32 func_00188F80(s32 arg0) {
    return func_00179258(D_0040F4D4 + 0xFA8, M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0), s32 *, 0));
}
