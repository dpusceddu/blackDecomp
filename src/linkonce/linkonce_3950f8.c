#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00395078();

void func_003950F8(s32 arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_5 != 0) {
        func_00395078(arg0, temp_5);
    }
    M2C_FIELD(arg0, s32 *, 0) = 0;
}
