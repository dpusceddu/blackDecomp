#include "auto/prelude.h"

extern void func_00118188(void *arg0, s32 arg1, s32 arg2, f32 fparg0);
extern f32 func_0010F740(s32);
extern s32 func_00118088(void *, s32);

s32 func_00116E28(void *arg0, s32 arg1) {
    func_00118188(arg0, M2C_FIELD(arg0, s32 *, 0x14), M2C_FIELD(arg0, s32 *, 0x18), func_0010F740(M2C_FIELD(arg0, s32 *, 0x1C)));
    func_00118088(arg0, arg1);
    return 1;
}
