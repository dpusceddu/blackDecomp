#include "auto/prelude.h"

extern s32 func_00316668();
extern s32 func_00317C20();
extern M2C_UNK D_00456358;
extern s32 func_00312C70();

void func_003145D0(void *arg0) {
    u8 temp_3;

    func_00316668();
    temp_3 = M2C_FIELD(arg0, u8 *, 0x1B);
    if (temp_3 & 1) {
        func_00317C20(&D_00456358, arg0);
        return;
    }
    if (!(temp_3 & 4)) {
        func_00312C70(arg0);
    }
}
