#include "auto/prelude.h"

extern s32 func_00193988();
extern s32 func_00181028();
extern s32 func_00180FE0();
extern s32 func_001880D8();

void func_0019B3F8(void **arg0)
{
  s8 *new_var;
  void *temp_3;
  func_00193988();
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    temp_3 = (*arg0) + 0x140;
    func_00180FE0(temp_3);
  }
  temp_3 = *arg0;
  new_var = ((s8 *) temp_3) + 0x290;
  if ((*((u8 *) new_var)) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
}
