#include "auto/prelude.h"

extern s32 func_00103908();
extern void * D_0040F0E0;
extern s32 func_001038A8();
extern s32 func_0014CCB0(void *, f32);
extern void ** D_0040F4D0;
extern s32 func_0012D5A8();

void func_0012D910(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x38) != 0) && (func_00103908(D_0040F0E0) == 0) && (func_001038A8(D_0040F0E0) == 0)) {
        func_0014CCB0(arg0 + 0x230, M2C_FIELD(D_0040F4D0, f32 *, 0x1C));
    }
    if ((M2C_FIELD(arg0, s32 *, 8) != M2C_FIELD(arg0, s32 *, 4)) || (M2C_FIELD(arg0, s32 *, 0) != 0x1C)) {
        func_0012D5A8(arg0);
    }
}
