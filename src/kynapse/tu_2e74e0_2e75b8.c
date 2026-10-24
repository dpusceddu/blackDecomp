#include "ps2/prelude.h"

extern M2C_UNK D_003EB3D0;
extern s32 func_0038E910();
extern M2C_UNK D_003EB3B8;
extern s32 func_0038EAA0();
extern M2C_UNK D_003EB3A0;
extern s32 D_003EAF88;
extern s32 D_003EB390;

void * func_002E75B8(void *arg0, void *arg1) {
    M2C_FIELD(arg0, void **, 4) = arg1;
    M2C_FIELD(arg0, M2C_UNK **, 0) = &D_003EB3D0;
    return arg0;
}

s32 func_002E75D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_0038E910(arg0, arg1, arg2, arg3, arg4 & 0xFF, arg5 & 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EB3B8;
    return arg0;
}

s32 func_002E7610(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_0038EAA0(arg0, arg1, arg2, arg3, arg4 & 0xFF, arg5 & 0xFF);
    M2C_FIELD(arg0, M2C_UNK **, 0x110) = &D_003EB3A0;
    return arg0;
}

void func_002E7650(void) {
    D_003EAF88 = 0;
}

void func_002E7660(void) {
    D_003EB390 = 0;
}
