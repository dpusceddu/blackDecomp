#include "auto/prelude.h"

extern s32 func_00312510(M2C_UNK *, M2C_UNK);
extern M2C_UNK D_003CEA88;
extern s32 func_00317C20(M2C_UNK *, void *);
extern M2C_UNK D_00455FE0;

s32 func_003128D8(void) {
    return func_00312510(&D_003CEA88, 0xF) != 0;
}

void func_00312900(void *arg0) {
    if (!(M2C_FIELD(arg0, s32 *, 0x1C) & 1)) {
        func_00317C20(&D_00455FE0, arg0);
    }
}
