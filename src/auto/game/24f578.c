#include "auto/prelude.h"

void func_0024F578(u32 *arg0) {
    u32 temp_6;
    u32 var_4;

    temp_6 = *arg0;
    var_4 = ((temp_6 >> 6) & 0xFFF) + 1;
    if (var_4 >= 0x1000U) {
        var_4 = 0xFFF;
        *arg0 = (temp_6 & 0xFEFFFFFF) | 0x01000000;
    }
    *arg0 = (*arg0 & 0xFFFC003F) | ((var_4 & 0xFFF) << 6);
}
