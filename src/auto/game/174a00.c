#include "auto/prelude.h"

extern void * func_00135550();
extern s32 func_0018D3A0();

void func_00174A00(s32 arg0, s64 *arg1) {
    s32 temp_17;

    if (arg1 != NULL) {
        temp_17 = M2C_FIELD(arg1, s32 *, 0xC4);
        if ((temp_17 == 1) && (func_00135550(arg1) != NULL) && (M2C_FIELD(func_00135550(arg1), s32 *, 0x80) == temp_17)) {
            func_0018D3A0(func_00135550(arg1) + 0xD10, arg0);
        }
    }
}
