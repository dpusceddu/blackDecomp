#include "auto/prelude.h"

extern s32 func_0034E220(s32, void *, void *, M2C_UNK, f32);
extern f32 * func_003500E0(void *arg0, s32 arg1);
extern s32 func_0034DE98();

void func_0034E4A8(s32 arg0, void *arg1, void *arg2) {
    func_0034E220(arg0, arg1, arg2, 0, *func_003500E0(arg2, M2C_FIELD(M2C_FIELD(arg1, void **, 8), s32 *, 0xC)));
}

f32 func_0034E508(void) {
    func_0034DE98();
    return 1.0f;
}
