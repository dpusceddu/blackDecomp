#include "auto/prelude.h"

extern s32 func_0035F660();
extern s32 func_0035E7D8(s32);
extern s32 func_0035C6EC(s32, M2C_UNK, s32);

void func_00312D48(void) {
    func_0035F660();
}

s32 func_00312D68(s32 arg0, s32 arg1) {
    s32 temp_17;
    s32 temp_2;

    temp_17 = arg0 * arg1;
    temp_2 = func_0035E7D8(temp_17);
    if (temp_2 != 0) {
        func_0035C6EC(temp_2, 0, temp_17);
    }
    return temp_2;
}
