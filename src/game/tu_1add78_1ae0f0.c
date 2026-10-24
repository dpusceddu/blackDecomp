#include "ps2/prelude.h"

extern s32 func_001ADF18();
extern s32 func_001ADF30();

s32 func_001AE0F0(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = arg0 + 0xC;
    func_001ADF18(temp_16, arg1);
    return func_001ADF30(temp_16, arg1);
}
