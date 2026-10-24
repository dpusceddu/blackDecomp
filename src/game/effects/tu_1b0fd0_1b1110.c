#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001B10F8();

void func_001B1110(void *arg0) {
    func_001B10F8();
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
}
