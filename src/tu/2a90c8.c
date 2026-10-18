#include "auto/prelude.h"

extern s32 (*D_004494D4)();
extern s32 func_002AC6E8(s32);

void func_002A90C8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x18)();
}

void func_002A90E8(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK (**)(), 0x1C)();
}

s32 func_002A9108(s32 arg0) {
    return (D_004494D4() == 0) ? 0 : arg0;
}

void * func_002A9140(void *arg0) {
    return (func_002AC6E8(M2C_FIELD(arg0, s32 *, 0x60)) == 0) ? NULL : arg0;
}
