#include "ps2/prelude.h"

void func_00173F58(void *arg0, void *arg1) {
    s128 temp_2;

    M2C_FIELD(arg0, void **, 0x10) = arg1;
    if (arg1 != NULL) {
        temp_2 = M2C_FIELD(arg1, s128 *, 0xA0);
        M2C_FIELD(arg0, s8 *, 0x40) = 0;
        M2C_FIELD(arg0, s128 *, 0x30) = temp_2;
        M2C_FIELD(arg0, s128 *, 0x50) = temp_2;
    }
}
