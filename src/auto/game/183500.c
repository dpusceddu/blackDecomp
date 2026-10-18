#include "auto/prelude.h"

s32 func_00183500(void *arg0)
{
  void *temp_2;
  temp_2 = *((void **) (((s8 *) arg0) + 0x30));
  if (temp_2 == NULL)
  {
    return 0;
  }
  if (arg0 || temp_2)
  {
    return *((s32 *) (((s8 *) temp_2) + (0x10 & 0xFFFFFFFFFFFFFFFFu)));
  }
  else
  {
    return M2C_FIELD(temp_2, s32 *, 0x10);
  }
}
