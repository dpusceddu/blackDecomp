#include "auto/prelude.h"

extern s32 func_0020DC20();
extern s32 func_0020DB90(s32 *, s32);

void func_0020DC60(s32 *arg0, s32 arg1) {
    s32 temp_17;

    temp_17 = arg1 + 1;
    if (*arg0 < temp_17) {
        func_0020DC20();
        func_0020DB90(arg0, temp_17);
    }
}
