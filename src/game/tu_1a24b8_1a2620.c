#include "ps2/prelude.h"

extern s32 func_00179258(s32, s32);
extern s32 D_0040F4D4;
extern s32 func_001A2C70();
extern void func_001A2CF0();

void func_001A2620(void *arg0) {
    func_00179258(D_0040F4D4 + 0xFA8, M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0x298));
}

void func_001A2650(void *arg0, s32 arg1) {
    if (arg1 == 1) {
        func_001A2C70();
        M2C_FIELD(arg0, s32 *, 0x50) = arg1;
    }
}

void func_001A2690(void) {

}

void func_001A2698(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        func_001A2CF0();
    }
}
