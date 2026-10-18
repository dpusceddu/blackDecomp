#include "auto/prelude.h"

extern s32 func_0027ACD0();
extern s32 func_002A90C8(s32);
extern s32 func_001C8560(s32, void *);
extern s32 D_0040F4C0;

void func_001B0910(void *arg0) {
    func_0027ACD0();
    M2C_FIELD(arg0, f32 *, 0x90) = (f32) (1.0f / M2C_FIELD(arg0, f32 *, 0x48));
}

void func_001B0948(void *arg0) {
    func_002A90C8(M2C_FIELD(arg0, s32 *, 0x58));
    func_001C8560(D_0040F4C0 + 0xCFD0, arg0);
}
