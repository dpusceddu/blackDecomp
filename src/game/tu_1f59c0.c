#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001F1C08();

void func_001F59C0(void *arg0) {
    func_001F1C08();
    M2C_FIELD(arg0, s8 *, 0x2B10) = 0;
}
