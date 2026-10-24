#include "ps2/prelude.h"

extern s32 func_0035CA74(s32);
extern s32 func_00250198();
extern s32 D_0043DEE0;
extern u16 D_003BFAF8;

s32 func_00387458(s32 *arg0) {
    return func_0035CA74(*arg0 + 8) == 0;
}

s32 func_00387480(s32 *arg0) {
    return func_0035CA74(*arg0 + 8) != 0;
}

void func_003874A8(u16 **arg0)
{
  u16 *temp_5;
  s8 *new_var2;
  s8 *new_var;
  int new_var3;
  u16 temp_2;
  temp_5 = *arg0;
  new_var2 = ((s8 *) temp_5) - -0;
  new_var = (s8 *) temp_5;
  temp_2 = (*((u16 *) new_var2) = (*((u16 *) (new_var + ((0, 0))))) - 1);
  if (!(temp_2 & 0xFFFF))
  {
    new_var3 = (M2C_FIELD(temp_5, u16 *, 4)) + 9;
    func_00250198(D_0043DEE0, temp_5, new_var3);
  }
  *arg0 = &D_003BFAF8;
  D_003BFAF8 += 1;
}
