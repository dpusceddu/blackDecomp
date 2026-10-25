#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_002E4DC8();
extern M2C_UNK D_0044FC20;
extern M2C_UNK func_002D86A8;
extern M2C_UNK * D_0044FD30;
extern M2C_UNK D_003E4728;

void func_002D8718(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E4DC8(&D_0044FC20, "CEntityCanFly", &func_002D86A8);
            return;
        }
        D_0044FD30 = &D_003E4728;
    }
}


void func_002D87E8(void) {
    func_002D8718(1, 0xFFFF);
}

void func_002D8808(void) {
    func_002D8718(0, 0xFFFF);
}
