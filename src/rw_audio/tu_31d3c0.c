#include "auto/prelude.h"

extern s32 func_00368738(s32, void *);

void * func_0031D3C0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    return (~func_00368738(M2C_FIELD(arg0, s32 *, 0), arg0) == 0) ? NULL : arg0;
}
