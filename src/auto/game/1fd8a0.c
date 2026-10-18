#include "auto/prelude.h"

extern s32 func_001F1C08();

void func_001FD8A0(void *arg0)
{
  void *new_var3;
  void *new_var;
  void *new_var2;
  s32 *temp_3;
  u32 var_4;
  func_001F1C08();
  var_4 = 0;
  do
  {
    new_var3 = (new_var = arg0 + 0x70);
    new_var2 = new_var3 + (var_4 * 4);
    temp_3 = new_var2;
    var_4 = (var_4 + 1) & 0xFF;
    *temp_3 = 0;
  }
  while (var_4 < 2U);
  M2C_FIELD(arg0, s32 *, 0x78) = 0;
}
