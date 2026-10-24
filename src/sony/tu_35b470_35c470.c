#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 D_0047EA08;

s32 func_0035C470(s32 arg0) {
    s32 temp_4;

    temp_4 = arg0 * 0x24;
    if (M2C_FIELD((temp_4 + ((s32) &D_0047EA08)), s32 *, 0) == 0) {
        return -1;
    }
    return M2C_FIELD((((s32) &D_0047EA08) + temp_4), s32 *, 4);
}
