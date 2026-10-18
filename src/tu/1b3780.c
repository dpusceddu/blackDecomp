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

void func_001B37B0(s32 arg0, s32 arg1)
{
  s8 *new_var;
  new_var = ((s8 *) (arg0 + ((arg1 & 0xFFFF) * 0x10))) + 0xD;
  *((s8 *) new_var) = 1;
}
