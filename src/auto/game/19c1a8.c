#include "auto/prelude.h"

extern s32 func_00193988();
extern s32 func_00188148(void *, M2C_UNK);
extern s32 func_00187FE0(s32, M2C_UNK);

void func_0019C1A8(s32 *arg0) {
    func_00193988();
    func_00188148(*arg0 + 0x290, 1);
}

void func_0019C1E0(s32 *arg0, s32 arg1) {
    if (arg1 == 3) {
        func_00187FE0(*arg0 + 0x290, 0);
    }
}
