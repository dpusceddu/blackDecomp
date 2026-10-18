#include "auto/prelude.h"

extern M2C_UNK D_00483AD8;

s32 func_0036A448(s32 arg0, s32 arg1)
{
  s32 temp_2;
  M2C_UNK *new_var;
  new_var = &D_00483AD8;
  temp_2 = M2C_FIELD(new_var, s32 *, 0x14);
  M2C_FIELD(new_var, s32 *, 0x14) = arg0;
  M2C_FIELD(new_var, s32 *, 0x18) = arg1;
  return temp_2;
}
