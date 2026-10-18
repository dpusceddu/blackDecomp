#include "auto/prelude.h"

extern M2C_UNK D_003EF7B0;

void *func_002FEAE0(void *arg0, void *arg1)
{
  *((void **) (((s8 *) arg0) + 4)) = arg1;
  *((M2C_UNK **) (((s8 *) arg0) + 0)) = &D_003EF7B0;
  M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 0x14));
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  if (arg0)
  {
  }
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
  return arg0;
}
