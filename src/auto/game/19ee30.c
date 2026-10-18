#include "auto/prelude.h"

extern f32 func_001891A8();
extern s32 func_001863A0();
extern s32 func_0019DFE8();
extern s32 func_0019DF50();

void func_0019EE30(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x45) != 0) {
        if (func_001891A8(M2C_FIELD(arg0, s32 *, 0) + 0x150) < 2.0f) {
            goto block_3;
        }
    } else {
block_3:
        func_001863A0(M2C_FIELD(arg0, s32 *, 0) + 0x90);
        func_0019DFE8(arg0);
    }
    func_0019DF50(arg0);
}
