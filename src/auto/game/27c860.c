#include "auto/prelude.h"

s8 *func_0027C860(s8 *arg0)
{
  s8 *var_5;
  u32 var_6;
  var_5 = arg0;
  var_6 = 0;
 do { } while (0);
  if ((*var_5) == 0x3A)
  {
    var_5 += 1;
  }
  else
  {
    loop_3:
    var_6 += 1;

    if (var_6 < 4U)
    {
 do { } while (0);
      if (!((*(var_5 + var_6)) == 0x3A))
      {
        goto loop_3;
      }
      else
      {
        var_5 += var_6 + 1;
      }
    }
  }
  return var_5;
}
