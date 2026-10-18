#include "auto/prelude.h"

extern s32 func_003165C8();
extern s32 func_00316618();

s32 func_0031DE30(s32 arg0, s32 arg1, s32 arg2) {
    func_003165C8(arg0, arg2);
    func_00316618(arg0, arg1);
    return arg0;
}

void *func_0031DE78(void *arg0)
{
  M2C_UNK (*temp_2)(M2C_UNK);
  unsigned short new_var;
  temp_2 = *((M2C_UNK (**)(M2C_UNK)) (0x3C + ((s8 *) arg0)));
  new_var = 0;
  if (temp_2 == ((void *) new_var))
  {
    if (temp_2)
    {
      return (void *) new_var;
    }
    else
    {
      return (void *) new_var;
    }
  }
  temp_2(new_var);
  return arg0;
}
