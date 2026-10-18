#include "auto/prelude.h"

extern s32 func_00183238(s32);
extern s32 func_00173F18();

s32 func_00174ED8(void) {
    return 1;
}

void func_00174EE0(void *arg0, void *arg1) {
    func_00183238(arg1 + 0x1EB0);
    func_00173F18(M2C_FIELD(arg0, void **, 0x90), arg1);
}
