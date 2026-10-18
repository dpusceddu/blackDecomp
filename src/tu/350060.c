#include "auto/prelude.h"

extern s32 func_0035C6EC();
extern s32 func_0035C544();

s32 func_00350060(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x118) = 0;
    func_0035C6EC(arg0, 0, 0x118);
    return arg0;
}

void func_00350098(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x118) = 0;
}

s32 func_003500A0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x118);
}

void func_003500A8(s32 arg0, s32 arg1) {
    if (arg0 != arg1) {
        M2C_FIELD(arg0, s32 *, 0x118) = (s32) M2C_FIELD(arg1, s32 *, 0x118);
        func_0035C544(arg0, arg1, M2C_FIELD(arg1, s32 *, 0x118) * 4);
    }
}
