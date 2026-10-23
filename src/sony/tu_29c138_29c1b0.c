#include "auto/prelude.h"

u32 func_0029C1B0(u32 arg0)
{
  u32 var_4;
  short pad;
  var_4 = arg0;
  if ((var_4 >> 0x1C) == 7)
  {
    var_4 = var_4 & 0x0FFFFFFF;
    var_4 = var_4 | 0x80000000;
  }
 do { } while (0);
  return var_4;
}
