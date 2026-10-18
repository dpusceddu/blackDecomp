#include "auto/prelude.h"

extern s32 func_001B0FF8();

s32 func_001BF720(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    return func_001B0FF8(arg0);
}
