#include "auto/prelude.h"

extern s32 func_002D15A0();
extern s32 func_002D8448();
extern s32 func_002DA1C8();
extern s32 func_002F0DA8();
extern s32 func_003054F8();
extern s32 func_0030D130();
extern s32 func_0016F9A8();
extern s32 func_0016EA80();
extern void func_0016FB48();

void func_0016ED80(void) {
    if ((func_002D15A0() != 0) && (func_002D8448() != 0) && (func_002DA1C8() != 0) && (func_002F0DA8() != 0) && (func_003054F8() != 0)) {
        func_0030D130();
    }
}

s32 func_0016EDF0(void *arg0) {
    func_0016F9A8();
    func_0016EA80(arg0 + 0x7C);
    func_0016EA80(arg0 + 0x88);
    func_0016FB48();
    M2C_FIELD(arg0, s8 *, 0x4C) = 1;
    return 1;
}
