#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0017DB98();
extern s32 func_00182318();

void func_001A13B8(void *arg0) {
    func_0017DB98(M2C_FIELD(arg0, s32 *, 0) + 0x650, M2C_FIELD(arg0, s128 *, 0x10));
    func_00182318(M2C_FIELD(arg0, s32 *, 0) + 0x810, 0);
}
