#include "auto/prelude.h"

extern s32 func_001AF298();

void func_001AF768(s32 arg0, s32 arg1)
{
  int new_var;
  s32 temp_5;
 do { new_var = (arg1 * 0x18) + 0xCA58; temp_5 = new_var; } while (0);
  func_001AF298(arg0 + temp_5, temp_5);
}
