#include "ps2/prelude.h"

extern s32 func_0023BC28();
extern s32 func_00237C18(s32, s32);
extern s32 func_00236AC0(s32, s32, s32);

void func_0023BCA0(void) {
    func_0023BC28();
}

s32 func_0023BCC0(void) {
    return func_0023BC28() != 0;
}

void func_0023BCE0(s32 arg0, s32 arg1, s32 arg2) {
    func_00237C18(arg1, arg2);
}

void func_0023BD00(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00236AC0(arg1, arg2, arg3);
}
