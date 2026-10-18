#include "auto/prelude.h"

extern M2C_UNK D_003E6438;
extern s32 func_002DADD0();
extern unsigned int D_003E0040;
extern s32 (*D_003C87E0)();

void func_002DC840(M2C_UNK **arg0, s32 arg1)
{
  *arg0 = &D_003E6438;
  arg0++;
  arg0--;
  func_002DADD0();
  *arg0 = &D_003E0040;
  if (arg1 & 1)
  {
    D_003C87E0(arg0);
  }
}
