#include "auto/prelude.h"

extern s32 func_00174210();
extern s32 func_00174218();
extern void func_0017B3C0(void *arg0);
extern s32 func_0017B930();
extern s32 func_0017B998(s32);

s32 func_0017B668(s32 arg0) {
    return func_00174210(arg0, 0x20);
}

s32 func_0017B688(void *arg0) {
    func_00174218();
    M2C_FIELD(arg0, s32 *, 0xC) = 0;
    func_0017B3C0(arg0 + 0x10);
    return 1;
}

void func_0017B6C0(s32 arg0) {
    func_0017B930();
    func_0017B998(arg0);
}

s32 func_0017B6F0(void) {
    return 1;
}
