#include "auto/prelude.h"

extern s32 func_0036CD08(M2C_UNK, s32, M2C_UNK);
extern void func_00324E38(s32 arg0, s32 arg1);

s32 func_00324DE8(s32 arg0) {
    s32 temp_2;

    temp_2 = func_0036CD08(0, arg0, 0);
    func_00324E38(temp_2, arg0);
    return temp_2;
}
