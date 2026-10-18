#include "auto/prelude.h"

extern f32 *func_003500E0();

f32 func_0034EAA0(void *arg0, void *arg1)
{
  s16 temp_5;
  temp_5 = M2C_FIELD(arg0, s16 *, 2);
  if (temp_5 >= 0x46)
  {
    if (arg1)
    {
      return M2C_FIELD(arg0, f32 *, 4);
    }
    else
    {
      return M2C_FIELD(arg0, f32 *, 4);
    }
  }
  return *func_003500E0(arg1, (s32) temp_5);
}
