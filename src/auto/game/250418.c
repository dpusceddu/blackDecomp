#include "auto/prelude.h"

extern s32 *func_00248C78();
extern s32 D_003BFAB8;
extern s32 func_002488D0();

s32 func_00250418(s32 arg0, s32 arg1, u16 **arg2, s32 arg3)
{
  if (func_00248C78(D_003BFAB8 + 8, arg2) == NULL)
  {
    func_002488D0(8 + arg0, arg2, arg3);
  }
  if (arg3 || arg2)
  {
    return 1;
  }
  else
  {
    return 1;
  }
}
