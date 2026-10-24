#include "ps2/prelude.h"

extern s32 func_001F2870();
extern s32 D_0040F51C;
extern void func_001F2838();
extern s32 func_0020B678();
extern void *D_0040F544;
extern M2C_UNK D_003FA300;

void func_0020AE20(void *arg0)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 0x3928;
  if ((M2C_FIELD(arg0, s32 *, 0x3924)) == 0)
  {
    *((s32 *) new_var) = func_001F2870(D_0040F51C, 0);
    func_001F2838(D_0040F51C, 0, 0);
    M2C_FIELD(arg0, s32 *, 0x3924) = 1;
    M2C_FIELD(arg0, s32 *, 0x44C) = 0;
    do
    {
      M2C_FIELD(arg0, s8 *, 0x454) = 0;
    }
    while (0);
  }
  func_0020B678(D_0040F544, &D_003FA300, 4);
}
