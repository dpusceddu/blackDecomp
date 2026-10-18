#include "auto/prelude.h"

volatile unsigned int func_00318250(s32 arg0, s32 arg1)
{
  s32 var_6;
  void *var_3;
  if (arg0)
  {
  }
  var_3 = *((void **) (((s8 *) arg0) + 4));
  var_6 = 0;
  if (var_3 == arg0)
  {
 goto dummy_label_525197; dummy_label_525197: ;
    do
    {
    }
    while (0);
    goto block_7;
  }
  loop_2:
  if ((M2C_FIELD(var_3, s32 *, 8)) == arg1)
  {
    goto block_4;
  }

  var_3 = *((void **) (((s8 *) var_3) + 4));
  goto block_6;
  block_4:
  return var_6;

  block_6:
  var_6 += 1;

  if (var_3 != arg0)
  {
    goto loop_2;
  }
  block_7:
  return -1;

}
