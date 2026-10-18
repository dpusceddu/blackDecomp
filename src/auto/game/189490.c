#include "auto/prelude.h"

extern s32 func_00173610();

s32 func_00189490(s32 arg0) {
    return (func_00173610((M2C_FIELD(arg0, s32 *, 0x120) * 0x60) + arg0 + 0x50) ^ 1) & 0xFF;
}
