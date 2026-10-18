#include "auto/prelude.h"

extern s32 func_0035C6EC();

s32 func_001EABA0(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 0x40) = -1;
    M2C_FIELD(arg0, s32 *, 0x44) = 0;
    M2C_FIELD(arg0, s32 *, 0x48) = 0;
    func_0035C6EC(arg0, 0, 0x40);
    return 1;
}

void func_001EABD8(void *arg0, s32 arg1, s32 arg2)
{
  s8 *new_var;
  s32 var_8;
  void *var_4;
  void *var_7;
  var_4 = arg0;
  var_7 = (void *) 0;
  var_8 = 0;
  loop_1:
  var_7 = ((M2C_FIELD(var_4, s32 *, 4)) == 0) ? (var_4) : (var_7);

  if ((M2C_FIELD(var_4, s32 *, 0)) != arg1)
  {
    var_8 += 1;
    var_4 += 8;
    if (var_8 >= 8)
    {
      if (var_7 != NULL)
      {
        new_var = (s8 *) var_7;
        *((s32 *) (new_var + 0)) = arg1;
 do { } while (0);
        M2C_FIELD(var_7, s32 *, 4) = arg2;
      }
    }
    else
    {
      goto loop_1;
    }
  }
}
