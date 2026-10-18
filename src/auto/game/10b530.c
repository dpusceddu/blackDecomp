#include "auto/prelude.h"

extern s32 func_00275340(void *);
extern s32 func_00275398(void *, M2C_UNK, void *);

s32 func_0010B530(void *arg0, void *arg1) {
    M2C_FIELD(arg0, s16 *, 0x4CA) = 0;
    M2C_FIELD(arg0, s16 *, 0x4CC) = 0;
    if ((arg1 != NULL) && (func_00275340(arg1) > 0)) {
        func_00275398(arg0 + 0x4CA, 0x14, arg1);
        return 1;
    }
    return 0;
}

s32 func_0010B590(s32 arg0) {
    return func_00275340(arg0 + 0x4CA) > 0;
}
