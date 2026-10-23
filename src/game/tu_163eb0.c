#include "auto/prelude.h"

extern void * func_00135550();
extern s32 func_0018ABE8();

void func_00163EB0(s32 arg0, s64 *arg1) {
    s32 temp_17;

    if (arg1 != NULL) {
        temp_17 = M2C_FIELD(arg1, s32 *, 0xC4);
        if ((temp_17 == 1) && (func_00135550(arg1) != NULL) && (M2C_FIELD(func_00135550(arg1), s32 *, 0x80) == temp_17)) {
            func_0018ABE8(func_00135550(arg1) + 0xD18, arg0);
        }
    }
}
