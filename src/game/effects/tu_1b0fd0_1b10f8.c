#include "include_asm.h"
#include "ps2/prelude.h"

void func_001B10F8(void *arg0) {
    M2C_FIELD(arg0, f32 *, 0x48) = (f32) (M2C_FIELD(arg0, f32 *, 0x4C) - M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), f32 *, 8));
}
