#include "auto/prelude.h"

extern s32 func_001749E8();
extern s32 func_00183688();
extern s32 func_001736B8();
extern s32 func_00183238(s32);
extern s32 func_00173F18();
extern s32 func_00173EE0();

s32 func_001750E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001749E8(arg0, 3, arg1, arg2, arg3);
    M2C_FIELD(arg0, s32 *, 0x48) = arg2;
    func_00183688(arg0 + 0x28, arg1, arg2);
    func_001736B8(arg0 + 0x50, 7);
    return 1;
}

s32 func_00175158(void) {
    return 1;
}

void func_00175160(s32 arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173F18(arg0 + 0x50, arg1);
}

void func_001751A0(s32 arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173EE0(arg0 + 0x50, arg1);
}
