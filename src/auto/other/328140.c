#include "auto/prelude.h"

void func_00328140(void *arg0, void *arg1) {
    if (M2C_FIELD(arg0, void **, 0x38) != NULL) {
        *M2C_FIELD(arg0, s32 **, 0x30) = 1;
    }
    if (arg1 != NULL) {
        M2C_FIELD(arg0, s32 *, 0xBC) = (s32) (((s32) M2C_FIELD(arg1, s32 *, 0x54) >> 1) & 1);
    }
    M2C_FIELD(arg0, void **, 0x38) = arg1;
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 0x40);
}

void func_00328180(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, u16 *, 0x5C) = (u16) (M2C_FIELD(arg0, u16 *, 0x5C) | 4);
    M2C_FIELD(arg0, f32 *, 0xA4) = (f32) ((fparg0 * 0.5f) + 0.5f);
}
