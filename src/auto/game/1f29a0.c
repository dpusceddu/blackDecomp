#include "auto/prelude.h"

extern void func_001F4D88();
extern void * D_0040F518;
extern s32 func_002019A0();
extern void func_001F4DE0();

void func_001F29A0(s32 arg0, s32 arg1, s32 arg2) {
    func_001F4D88(M2C_FIELD(D_0040F518, s32 *, 0x14));
    func_002019A0(M2C_FIELD(D_0040F518, s32 *, 0x2C), arg2);
}

void func_001F29E8(s32 arg0, s32 arg1, s32 arg2) {
    func_001F4DE0(M2C_FIELD(D_0040F518, s32 *, 0x14));
    func_002019A0(M2C_FIELD(D_0040F518, s32 *, 0x2C), arg2);
}
