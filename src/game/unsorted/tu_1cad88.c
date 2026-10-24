#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00108328();
extern s32 D_0040F4C4;

void func_001CAD88(s32 arg0, void *arg1, s32 arg2)
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
