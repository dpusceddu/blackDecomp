#include "auto/prelude.h"

extern s32 func_002D2CE8();

f32 func_002D2F80(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 fparg0) {
    return (fparg0 / (f32) (arg3 + 1)) / (f32) ((arg2 * 0xA) + 1);
}

void func_002D2FB8(void) {
    func_002D2CE8(1, 0xFFFF);
}

void func_002D2FD8(void) {
    func_002D2CE8(0, 0xFFFF);
}
