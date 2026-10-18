#include "auto/prelude.h"

extern s32 func_0032E3D0();

void * func_0032E5D8(void *arg0) {
    u8 sp[24] __attribute__((aligned(16)));
    func_0032E3D0(sp);
    M2C_FIELD(arg0, s32 *, 4) = 0x80;
    M2C_FIELD(arg0, s32 *, 0) = *(s32 *)(sp + 16);
    return arg0;
}
