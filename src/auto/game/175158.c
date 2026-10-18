#include "auto/prelude.h"

extern s32 func_00183238(s32);
extern s32 func_00173F18();
extern s32 func_00173EE0();

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
