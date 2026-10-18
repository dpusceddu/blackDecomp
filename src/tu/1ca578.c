#include "auto/prelude.h"

extern s32 func_00108328();
extern s32 D_0040F4C4;

void func_001CA578(s32 arg0, s32 arg1)
{
  s32 temp_2;
  int new_var;
  s8 *new_var2;
  s32 temp_2_2;
  temp_2_2 = M2C_FIELD(arg1, s32 *, 4);
  new_var = temp_2_2 != 0;
  new_var2 = ((s8 *) arg1) + 4;
  temp_2 = temp_2_2 + arg1;
  if (new_var)
  {
    *((s32 *) new_var2) = temp_2_2 + arg1;
  }
  return temp_2_2 + arg1;
}

void func_001CA590(s32 arg0, void *arg1, s32 arg2)
{
  s32 temp_2;
  s32 *new_var;
  s32 *new_var2;
  new_var = &(M2C_FIELD(arg1, s32 *, 4));
  temp_2 = *new_var;
  if (temp_2 != 0)
  {
    new_var2 = &(*((s32 *) (((s8 *) (((temp_2 - 1) * 4) + arg2)) + 0)));
    M2C_FIELD(arg1, s32 *, 4) = func_00108328(D_0040F4C4, *new_var2);
  }
}

void func_001CA5D8(void) {

}
