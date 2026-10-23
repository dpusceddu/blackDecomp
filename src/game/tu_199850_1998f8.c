#include "auto/prelude.h"

extern s32 func_00180BC0(s32);
extern s32 func_00193A28(void **, M2C_UNK, M2C_UNK);
extern s32 func_00177F18(s32);
extern s32 func_0017B268(s32);

void func_001998F8(void **arg0) {
    if (func_00180BC0(*arg0 + 0xB30) == 0) {
        func_00193A28(arg0, 0xC, 0);
        return;
    }
    func_00193A28(arg0, 0x37, 0);
}

void func_00199950(s32 *arg0) {
    func_00177F18(*arg0 + 0x1F00);
    func_0017B268(*arg0 + 0x1F60);
}
