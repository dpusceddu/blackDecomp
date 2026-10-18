#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_0033A488();

s32 func_0033AE40(s32 arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 0x100) = 0;
    M2C_FIELD(arg0, s32 *, 0x18) = (s32) M2C_FIELD(arg0, s32 *, 0x1C);
    return func_0033A488(arg0, arg1, arg2);
}
