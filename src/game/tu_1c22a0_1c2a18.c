#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001CFAC8();

void func_001C2A18(void *arg0) {
    func_001CFAC8();
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s32 *, 0) = 0;
}
