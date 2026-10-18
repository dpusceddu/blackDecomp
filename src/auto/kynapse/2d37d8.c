#include "auto/prelude.h"

extern void * D_003C9ED4;

void func_002D37D8(void *arg0, f32 fparg0) {
    f32 temp_f12;

    temp_f12 = fparg0 * M2C_FIELD(D_003C9ED4, f32 *, 0xC);
    if (M2C_FIELD(arg0, f32 *, 0x40) != temp_f12) {
        M2C_FIELD(arg0, f32 *, 0x40) = temp_f12;
        M2C_FIELD(arg0, s8 *, 0x38) = 0;
    }
}

void func_002D3810(void *arg0, f32 fparg0) {
    if (M2C_FIELD(arg0, f32 *, 0x44) != fparg0) {
        M2C_FIELD(arg0, f32 *, 0x44) = fparg0;
        M2C_FIELD(arg0, s8 *, 0x38) = 0;
    }
}

f32 func_002D3838(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0x40) / M2C_FIELD(D_003C9ED4, f32 *, 0xC);
}
