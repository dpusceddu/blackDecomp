#include "auto/prelude.h"

extern s32 func_002819E0();
extern s32 func_00280908(s32, s32);

void func_00281948(s32 arg0, s32 arg1) {
    func_002819E0();
    func_00281988(arg0, arg1);
}

void func_00281988(s32 arg0, s32 arg1) {
    s32 var_16;
    u32 var_17;

    var_16 = arg0 + 0xE00;
    var_17 = 0;
    do {
        func_00280908(var_16, arg1);
        var_17 += 1;
        var_16 += 0x3C;
    } while (var_17 < 0x23U);
}
