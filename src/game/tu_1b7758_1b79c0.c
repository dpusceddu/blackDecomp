#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_001B7A70();

s32 func_001B79C0(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_8;

    temp_8 = M2C_FIELD(arg0, void **, 0x1A010);
    return func_001B7A70(arg0, M2C_FIELD(((arg2 * 4) + M2C_FIELD(temp_8, s32 *, 0x24)), s32 *, 0), arg1, 0, (s32) temp_8);
}
