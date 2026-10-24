#include "ps2/prelude.h"

extern void *D_003D6944;
extern void *func_0035E7D8();

s32 func_0035E690(s32 arg0)
{
  s32 temp_4;
  void *var_5;
  s8 *new_var;
  var_5 = *((void **) (((s8 *) D_003D6944) + 0x148));
  if (var_5 == NULL)
  {
    var_5 = D_003D6944 + 0x14C;
    *((void **) (((s8 *) D_003D6944) + 0x148)) = var_5;
  }
  if ((M2C_FIELD(var_5, s32 *, 4)) >= 0x20)
  {
    var_5 = func_0035E7D8(0x88U, var_5);
    if (var_5 != NULL)
    {
      M2C_FIELD(var_5, s32 *, 4) = 0;
      *((void **) (((s8 *) var_5) + 0)) = (void *) (*((void **) (((s8 *) D_003D6944) + 0x148)));
      *((void **) (((s8 *) D_003D6944) + 0x148)) = var_5;
      goto block_8;
    }
    return -1;
  }
  block_8:
  temp_4 = M2C_FIELD(var_5, s32 *, 4);

  new_var = ((s8 *) (var_5 + (temp_4 * 4))) + 8;
  *((s32 *) new_var) = arg0;
  M2C_FIELD(var_5, s32 *, 4) = (s32) (temp_4 + 1);
  return 0;
}
