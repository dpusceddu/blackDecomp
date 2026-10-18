#include "auto/prelude.h"

s32 func_001AFDA8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 4);
}

f32 func_001AFDB0(f32 *arg0) {
    return *arg0;
}

s32 func_001AFDB8(s32 arg0) {
    if (arg0 == 0) {
        goto block_3;
    }
    if (arg0 == 1) {
        goto block_4;
    }
    return 1;
block_3:
    return 4;
block_4:
    return 2;
}
