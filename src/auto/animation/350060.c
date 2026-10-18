#include "auto/prelude.h"

extern s32 func_0035C6EC();

s32 func_00350060(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x118) = 0;
    func_0035C6EC(arg0, 0, 0x118);
    return arg0;
}
