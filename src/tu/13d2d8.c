#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 func_0013EE38();
extern s32 func_001814E8();
extern s32 func_0013EE48();
extern s32 func_0018C368();
extern s32 func_00181560();
extern s32 func_0018D580();
extern s32 func_001796E0();
extern s32 D_0040F4D4;
extern s32 func_0017B220();
extern s32 func_0017BA00();
extern s32 func_0016DDE0();

void func_0013D2D8(s32 arg0) {
    func_0013EE38();
    func_001814E8(arg0 + 0xEC0);
}

s32 func_0013D308(s32 arg0) {
    s32 temp_16;

    temp_16 = arg0;
    func_0013EE48(arg0);
    func_0018C368(temp_16 + 0x1DA0);
    func_00181560(temp_16 + 0xEC0);
    func_0018D580(temp_16 + 0xD10);
    func_001796E0(D_0040F4D4, temp_16);
    func_0017B220(D_0040F4D4 + 0x1150, temp_16);
    func_0017BA00(D_0040F4D4 + 0x1290, temp_16);
    return func_0016DDE0(D_0040F4D4, temp_16);
}
