#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_00395668();

void func_003956E8(s32 arg0) {
    s32 temp_5;

    temp_5 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_5 != 0) {
        func_00395668(arg0, temp_5);
    }
    M2C_FIELD(arg0, s32 *, 0) = 0;
}
