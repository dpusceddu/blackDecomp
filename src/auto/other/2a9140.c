#include "auto/prelude.h"

extern s32 func_002AC6E8(s32);

void * func_002A9140(void *arg0) {
    return (func_002AC6E8(M2C_FIELD(arg0, s32 *, 0x60)) == 0) ? NULL : arg0;
}
