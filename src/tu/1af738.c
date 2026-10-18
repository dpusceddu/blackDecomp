#include "auto/prelude.h"

extern s32 func_001AF1C0();
extern s32 func_001AF298();

void * func_001AF738(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6, void *arg7) {
    return func_001AF1C0(arg0 + ((M2C_FIELD(arg1, u8 *, 9) * 0x18) + 0xCA58), arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}

void func_001AF768(s32 arg0, s32 arg1)
{
  int new_var;
  s32 temp_5;
 do { new_var = (arg1 * 0x18) + 0xCA58; temp_5 = new_var; } while (0);
  func_001AF298(arg0 + temp_5, temp_5);
}
