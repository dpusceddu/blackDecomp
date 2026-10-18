#include "auto/prelude.h"

extern s32 func_00280100(void *, s32);
extern void * D_0040F510;
extern void * D_0040F50C;

s32 func_001E79F0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 8) != 3) {
        func_00280100(D_0040F510, M2C_FIELD(arg0, s32 *, 4));
        M2C_FIELD(arg0, s32 *, 4) = 0;
        M2C_FIELD(D_0040F50C, s32 *, 0x948) = 0;
        M2C_FIELD(arg0, s32 *, 8) = 3;
    }
    return 1;
}
