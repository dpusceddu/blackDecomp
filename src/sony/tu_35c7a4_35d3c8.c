#include "ps2/prelude.h"

s32 func_0035D3C8(s32 arg0, s32 arg1)
{
  s32 var_16;
  s32 var_19;
  void *var_17;
  void *var_18;
  var_18 = arg0 + 0x1D8;
  var_19 = 0;
  if (var_18 != NULL)
  {
    do
    {
      var_16 = M2C_FIELD(var_18, s32 *, 4);
      var_16 = var_16 - 1;
      var_17 = *((void **) (((s8 *) var_18) + 8));
      if (var_16 >= 0)
      {
        do
        {
          if ((M2C_FIELD(var_17, s16 *, 0xC)) != 0)
          {
            var_19 |= ((s32 (*)(void *)) arg1)(var_17);
          }
          var_16 -= 1;
          var_17 += 0x58;
        }
        while (var_16 >= 0);
      }
      var_18 = *((void **) (((s8 *) var_18) + 0));
    }
    while (var_18 != NULL);
  }
  return var_19;
}
