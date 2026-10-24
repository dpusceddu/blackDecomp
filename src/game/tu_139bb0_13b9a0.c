#include "ps2/prelude.h"

extern s32 func_0013BAF8();
extern s32 func_00133ED8();
extern s32 func_0013BB38();
extern s32 func_00133FA0();
extern s32 func_0013F328(s32);
extern s32 func_001306A0();
extern void func_0013F0A8(void *arg0);
extern void func_0013DB40(void *arg0);
extern s32 func_0013F3E0();
extern s32 func_001306D0();
extern s32 func_0013F0D8();
extern s32 func_0013DBA0();
extern s32 D_0040F4D0;

s32 func_0013B9A0(s32 arg0) {
    func_0013BAF8();
    func_00133ED8(arg0);
    return 1;
}

void func_0013B9D0(s32 arg0) {
    func_0013BB38();
    func_00133FA0(arg0);
}

void func_0013BA00(s32 arg0) {
    func_0013F328(arg0 + 0x4F0);
    func_001306A0(arg0 + 0x620);
    func_0013F0A8(arg0 + 0x730);
    func_0013DB40(arg0 + 0x7D0);
}

s32 func_0013BA40(s32 arg0) {
    if ((func_0013F3E0(arg0 + 0x4F0, (s32) M2C_FIELD(arg0, s8 *, 0x418), arg0) != 0) && (func_001306D0(arg0 + 0x620, arg0, (s32) M2C_FIELD(arg0, s8 *, 0x418)) != 0) && (func_0013F0D8(arg0 + 0x730, (s32) M2C_FIELD(arg0, s8 *, 0x418), arg0) != 0) && (func_0013DBA0(arg0 + 0x7D0, arg0) != 0)) {
        M2C_FIELD(arg0, f32 *, 0x8AC) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
        return 1;
    }
    return 0;
}
