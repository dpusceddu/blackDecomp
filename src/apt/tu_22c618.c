#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_002523C0();

s32 func_0022C618(s32 arg0, s32 arg1) {
    s32 temp_6;

    temp_6 = (M2C_FIELD(arg1, s32 *, 0) + 3) & 0xFFFFFFFC;
    M2C_FIELD(arg1, s32 *, 0) = (s32) (temp_6 + 4);
    return func_002523C0(M2C_FIELD(temp_6, s32 *, 0), M2C_FIELD(((M2C_FIELD(arg0, s32 *, 0) * 4) + M2C_FIELD(arg0, s32 *, 8)), s32 *, -4));
}

void func_0022C668(void *arg0, s32 *arg1) {
    s32 temp_2;

    temp_2 = (*arg1 + 3) & 0xFFFFFFFC;
    *arg1 = temp_2 + 8;
    M2C_UNALIGNED64(arg0, 0x34) = (s64) M2C_UNALIGNED64(temp_2, 0);
}
