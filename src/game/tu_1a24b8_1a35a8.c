#include "auto/prelude.h"

extern s32 func_001A24B8();

s32 func_001A35A8(void *arg0)
{
  s8 *new_var;
  func_001A24B8();
  M2C_FIELD(arg0, s8 *, 0x82) = 0;
  new_var = (s8 *) (((s8 *) arg0) + 0x81);
  M2C_FIELD(arg0, s8 *, 0x80) = 0;
  *new_var = 1;
  return 1;
}
