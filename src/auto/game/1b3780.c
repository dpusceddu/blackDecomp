#include "auto/prelude.h"

void func_001B3780(s32 arg0) {
    u32 var_5;
    void *temp_3;

    var_5 = 0;
    do {
        temp_3 = arg0 + (var_5 * 0x10);
        var_5 = (var_5 + 1) & 0xFFFF;
        M2C_FIELD(temp_3, s8 *, 0xD) = 0;
    } while (var_5 < 0x1CU);
}
