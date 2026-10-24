#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00316400();
extern s32 D_003CED40;

s32 func_003150D0(void *arg0, void *arg1)
{
  s8 *new_var;
  s32 var_18;
  u32 temp_3;
  new_var = (s8 *) arg0;
  var_18 = 0;
  if ((M2C_FIELD(arg1, u16 *, 0xC)) == (*((u16 *) (new_var + 4))))
  {
    temp_3 = M2C_FIELD(arg1, u32 *, 0);
 var_18 = 0; if (temp_3 >= ((u32) (M2C_FIELD(arg0, u32 *, 8)))) {
      var_18 = 0;
      if (((u32) (M2C_FIELD(arg0, u32 *, 0xC))) >= temp_3)
      {
        var_18 = 0;
        if (func_00316400(M2C_FIELD(arg1, s32 *, 4), *((M2C_UNK **) (new_var + 0))) == 0)
        {
          var_18 = (((M2C_FIELD(arg1, u8 *, 0x18)) & 1) ^ ((M2C_FIELD(arg0, u8 *, 0x10)) & 1)) ^ 1;
          goto block_5;
        }
      }
    }
  }
  else
  {
    block_5:
    var_18 = var_18;

  }
  return var_18;
}

s32 func_00315168(s32 arg0) {
    return (&D_003CED40)[arg0];
}
