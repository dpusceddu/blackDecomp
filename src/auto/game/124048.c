#include "auto/prelude.h"

extern s32 func_0026F340();
extern s32 func_0027F640();

void func_00124048(void *arg0) {
    u8 sp[8];
    func_0026F340(sp);
    M2C_FIELD(arg0, s32 *, 0) = func_0027F640(sp);
    M2C_FIELD(arg0, s8 *, 0x6A5) = 0;
}
