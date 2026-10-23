#include "auto/prelude.h"

extern M2C_UNK D_003EE538;
extern s32 func_002F8C38();
extern unsigned int D_003E0040;
extern s32 (*D_003C87E0)();

void func_002FB4D8(M2C_UNK **arg0, s32 arg1)
{
  *arg0 = &D_003EE538;
  arg0++;
  arg0--;
  func_002F8C38();
  *arg0 = &D_003E0040;
  if (arg1 & 1)
  {
    D_003C87E0(arg0);
  }
}
