#include "include_asm.h"
#include "ps2/prelude.h"

void func_0038FFD0(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x18) = arg1;
}

s32 func_0038FFD8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x18);
}

s32 func_0038FFE0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 8);
}

s32 func_0038FFE8(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC);
}

s32 func_0038FFF0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x10);
}
