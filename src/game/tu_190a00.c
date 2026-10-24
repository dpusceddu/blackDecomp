#include "ps2/prelude.h"

extern s32 func_00188F10();
extern s32 func_0018D610();
extern s32 func_0018E4C0();

void func_00190A00(void *arg0, s32 *arg1) {
    if ((*arg1 == 3) && (func_00188F10(M2C_FIELD(arg0, s32 *, 4) + 0x150) == 0)) {
        func_0018D610(M2C_FIELD(arg0, s32 *, 4) + 0xD10);
    }
    func_0018E4C0(arg0, arg1);
}
