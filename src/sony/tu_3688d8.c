#include "ps2/prelude.h"

extern M2C_UNK D_004835C0;

M2C_UNK *func_003688D8(s32 arg0)
{
  M2C_UNK *new_var;
  void *temp_4;
  new_var = &D_004835C0;
  M2C_FIELD(new_var, s32 *, 0) = arg0;
  M2C_FIELD(new_var, s32 *, 4) = 0;
  temp_4 = new_var;
  temp_4 = temp_4 + 0x10;
  *((void **) (((s8 *) new_var) + ((unsigned short) 0xC))) = temp_4;
  *((void **) (((s8 *) new_var) + 8)) = temp_4;
  return new_var;
}
