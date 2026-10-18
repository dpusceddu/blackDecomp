#include "auto/prelude.h"

extern s32 func_00324E38();

void func_00313E60(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s32 *, 0x28) = (s32) M2C_FIELD(arg1, s32 *, 0);
    M2C_FIELD(arg0, s32 *, 0x2C) = (s32) M2C_FIELD(arg1, s32 *, 4);
    M2C_FIELD(arg0, u8 *, 0x1B) = (u8) (M2C_FIELD(arg0, u8 *, 0x1B) | M2C_FIELD(arg1, u8 *, 8));
}

void func_00313E88(void) {
    func_00324E38();
}
