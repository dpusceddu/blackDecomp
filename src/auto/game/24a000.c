#include "auto/prelude.h"

extern s32 func_00249F28();
extern s32 (*D_0043DAE8)();

s32 func_0024A000(s32 arg0, s32 arg1) {
    s32 temp_16;

    temp_16 = arg0 + 0x220;
    func_00249F28(temp_16, arg1, temp_16);
    return D_0043DAE8(temp_16);
}
