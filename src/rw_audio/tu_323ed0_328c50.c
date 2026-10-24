#include "ps2/prelude.h"

extern s32 func_00315F28();
extern s32 (*D_003D1140)();
extern s32 func_00329848();
extern M2C_UNK D_0045C120;

void func_00328C50(void) {
    func_00315F28();
}

s32 func_00328C70(void)
{
  int new_var;
  if (D_003D1140 == NULL)
  {
    if (D_003D1140)
    {
      return func_00329848(&D_0045C120) * (*((s32 *) (((s8 *) (&D_0045C120)) + 0x14)));
    }
    else
    {
      new_var = func_00329848(&D_0045C120) * (*((s32 *) (((s8 *) (&D_0045C120)) + 0x14)));
      return new_var;
    }
  }
  return D_003D1140();
}
