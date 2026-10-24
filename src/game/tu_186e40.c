#include "ps2/prelude.h"

extern s32 func_001776A0(s32, s32);
extern s32 D_0040F4D4;

void func_00186E40(void *arg0) {
    func_001776A0(D_0040F4D4 + 0x78, M2C_FIELD(arg0, s32 *, 0x7C));
}
