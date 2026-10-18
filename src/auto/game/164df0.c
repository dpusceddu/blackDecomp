#include "auto/prelude.h"

extern s32 func_001D8BC0(s32, s32, s32, s32, f32);
extern void * D_0040F510;

void func_00164DF0(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x190);
    func_001D8BC0(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0x34), M2C_FIELD(temp_3, s32 *, 0x50), M2C_FIELD(temp_3, u8 *, 0x59) != 0, M2C_FIELD(temp_3, u8 *, 0x58) != 0, M2C_FIELD(temp_3, f32 *, 0x54));
}

void func_00164E40(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x131) = 0;
    M2C_FIELD(arg0, s8 *, 0x130) = 1;
}

s32 func_00164E50(void *arg0, s64 arg1, s32 arg2) {
    M2C_FIELD(arg0, s64 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 0x134) = arg2;
    M2C_FIELD(arg0, s8 *, 0x130) = 1;
    M2C_FIELD(arg0, s8 *, 0x131) = 0;
    return 1;
}
