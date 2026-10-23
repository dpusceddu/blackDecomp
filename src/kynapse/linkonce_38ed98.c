#include "auto/prelude.h"

extern s32 D_003C95A4;
extern f32 D_003C958C;
extern f32 D_003C9590;
extern f32 D_003C95AC;
extern f32 D_003C95A8;

void func_0038ED98(s32 arg0) {
    D_003C95A4 = arg0;
}

f32 func_0038EDA8(void) {
    return D_003C958C;
}

f32 func_0038EDB8(void) {
    return D_003C9590;
}

f32 func_0038EDC8(void) {
    return D_003C95AC;
}

u8 func_0038EDD8(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x50);
}

void func_0038EDE0(f32 fparg0) {
    D_003C95A8 += fparg0;
}

f32 func_0038EDF8(void) {
    return D_003C95A8;
}
