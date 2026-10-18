#include "auto/prelude.h"

s32 func_001C2E40(void *arg0, void *arg1)
{
  f32 new_var;
  void *new_var2;
  s32 var_2;
  new_var = M2C_FIELD(arg0, f32 *, 4);
  var_2 = -1;
  new_var2 = arg1;
  if (!((M2C_FIELD(new_var2, f32 *, 4)) < new_var))
  {
    var_2 = 1;
  }
  return var_2;
}
