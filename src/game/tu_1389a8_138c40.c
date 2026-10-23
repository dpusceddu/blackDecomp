#include "auto/prelude.h"

extern void * D_0040F540;

void * func_00138C40(void *arg0, void *arg1) {
    return arg0 + (((s32) arg1 << 6) + 0x7A10);
}

s32 func_00138C50(void) {
    return M2C_FIELD(M2C_FIELD(D_0040F540, void **, 0x7C), s32 *, 0x14);
}

s32 func_00138C68(void) {
    return M2C_FIELD(M2C_FIELD(D_0040F540, void **, 0x7C), s32 *, 0x18);
}
