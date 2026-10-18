#include "auto/prelude.h"

s32 func_0034F2D0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x998) != 0;
}

f32 func_0034F2E0(void *arg0)
{
  f32 temp_f1;
  temp_f1 = M2C_FIELD(arg0, f32 *, 0x9C8);
  if (temp_f1 == 0.0f)
  {
    return 59.94f;
  }
  if (temp_f1)
  {
    return temp_f1 * 59.94f;
  }
  else
  {
    return temp_f1 * 59.94f;
  }
}
