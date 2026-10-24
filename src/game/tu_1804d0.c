#include "ps2/prelude.h"

extern s32 func_0017B260();

s32 func_001804D0(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x140) = arg1;
    return func_0017B260(arg0 + 0x110, arg1);
}
