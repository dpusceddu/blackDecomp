#include "auto/prelude.h"

extern s32 func_00249958(s32, s32);
extern s32 func_002487E0(s32);
extern s32 func_0024B3B0();

s32 func_0024F760(s32 arg0) {
    return arg0 + 8;
}

s32 func_0024F768(void) {
    return 1;
}

void func_0024F770(s32 arg0) {
    func_00249958(arg0 + 8, arg0);
}

void func_0024F790(void *arg0) {
    func_002487E0(arg0 + 8);
}

void func_0024F7B0(void) {
    func_0024B3B0();
}
