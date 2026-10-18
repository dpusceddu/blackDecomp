#include "auto/prelude.h"

extern void func_00209CF0();

void func_00209CC0(void *arg0) {
    s32 temp_2;

    temp_2 = M2C_FIELD(arg0, s32 *, 0xC) - 1;
    M2C_FIELD(arg0, s32 *, 0xC) = temp_2;
    if (temp_2 <= 0) {
        func_00209CF0();
    }
}
