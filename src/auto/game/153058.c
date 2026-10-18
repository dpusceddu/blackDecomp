#include "auto/prelude.h"

extern s32 func_0014B8A0();
extern s32 func_0014B948();

void func_00153058(void) {
    func_0014B8A0();
}

s32 func_00153078(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_0014B948(arg0, arg1, arg2 & 0xFF, arg3);
    return 1;
}
