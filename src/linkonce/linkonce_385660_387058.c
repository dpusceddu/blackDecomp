#include "ps2/prelude.h"

void func_00387058(s32 *arg0, s32 arg1)
{
  int new_var;
  new_var = (arg1 != 0) & 0xFFFFFFFF;
  *arg0 = ((*arg0) & 0xFEFFFFFF) | ((new_var << 0x18) ^ 0);
}

u32 func_00387080(u32 *arg0) {
    return (u32) *arg0 >> 0x19;
}

void func_00387090(s32 *arg0, u32 arg1) {
    u32 var_5;

    var_5 = arg1;
    if (var_5 >= 0x1000U) {
        var_5 = 0xFFF;
        *arg0 = (*arg0 & 0xFEFFFFFF) | 0x01000000;
    }
    *arg0 = (*arg0 & 0xFFFC003F) | ((var_5 & 0xFFF) << 6);
}

void func_003870E0(s32 *arg0, s32 arg1) {
    *arg0 = (*arg0 & 0x01FFFFFF) | (arg1 << 0x19);
}
