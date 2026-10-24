#include "ps2/prelude.h"

extern s32 func_00140008(s32);
extern s32 func_00131078();
extern s32 func_0013F298(s32);
extern s32 func_0013DEF0(void *arg0);
extern s32 func_00140048(s32);
extern s32 func_001310B8();
extern s32 func_0013F2C8(s32);
extern void func_0013DF38(s32);

void func_0013BAF8(s32 arg0) {
    func_00140008(arg0 + 0x4F0);
    func_00131078(arg0 + 0x620);
    func_0013F298(arg0 + 0x730);
    func_0013DEF0(arg0 + 0x7D0);
}

void func_0013BB38(s32 arg0) {
    func_00140048(arg0 + 0x4F0);
    func_001310B8(arg0 + 0x620);
    func_0013F2C8(arg0 + 0x730);
    func_0013DF38(arg0 + 0x7D0);
}
