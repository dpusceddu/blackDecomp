#include "auto/prelude.h"

extern void * D_003C9ED4;
extern s32 func_002D6FA8();

void func_002D71E8(void *arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x10) = (f32) (fparg0 * M2C_FIELD(D_003C9ED4, f32 *, 0xC));
}

f32 func_002D7200(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x10) / M2C_FIELD(D_003C9ED4, f32 *, 0xC);
}

void func_002D7220(void) {
    func_002D6FA8(1, 0xFFFF);
}

void func_002D7240(void) {
    func_002D6FA8(0, 0xFFFF);
}
