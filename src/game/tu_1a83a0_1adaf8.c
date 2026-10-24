#include "ps2/prelude.h"

extern s32 func_001AB1C0();
extern s32 D_003BD190;

s32 func_001ADAF8(s32 arg0, s32 arg1, s32 arg2) {
    return func_001AB1C0(arg0, arg1, D_003BD190, arg0 + 0x60, (s32) "S_126", arg2);
}
