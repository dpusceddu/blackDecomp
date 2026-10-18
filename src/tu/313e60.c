#include "auto/prelude.h"

extern s32 func_00324E38();
extern s32 func_00324D98();

void func_00313E60(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) | M2C_FIELD(arg1, u8 *, 8));
}

void func_00313E88(void) {
    func_00324E38();
}

s32 func_00313EA8(s32 arg0) {
    return func_00324D98(arg0, 0);
}

void * func_00313EC8(void *arg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), M2C_UNK (**)(), 0x24)();
    return arg0;
}
