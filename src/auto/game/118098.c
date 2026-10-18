#include "auto/prelude.h"

extern f32 func_00118210();

s32 func_00118098(void)
{
  s32 var_2;
  f32 new_var;
  new_var = func_00118210();
  var_2 = 1;
  if (!(new_var >= 1.0f))
  {
    var_2 = 0;
  }
  return var_2;
}
