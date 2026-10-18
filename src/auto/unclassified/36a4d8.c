#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 D_00483AE4;
extern s32 D_00483AEC;

void func_0036A4D8(s32 arg0) {
    if (arg0 < 0) {
        M2C_FIELD((((arg0 & 0x7FFFFFFF) * 0xC) + D_00483AE4), s32 *, 0) = 0;
        return;
    }
    M2C_FIELD(((arg0 * 0xC) + D_00483AEC), s32 *, 0) = 0;
}
