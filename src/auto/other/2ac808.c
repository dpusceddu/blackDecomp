#include "auto/prelude.h"

extern s32 (*D_004494E0)();

void * func_002AC808(void *arg0) {
    D_004494E0(0, arg0, 0);
    M2C_FIELD(arg0, u8 *, 0x22) = (u8) (M2C_FIELD(arg0, u8 *, 0x22) & 0xE7);
    return arg0;
}
