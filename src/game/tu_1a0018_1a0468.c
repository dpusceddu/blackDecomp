#include "ps2/prelude.h"

extern s32 func_001880D8();
extern s32 func_00193988();

void func_001A0468(void **arg0)
{
  void *temp_3;
  s8 *new_var2;
  int new_var;
  temp_3 = *arg0;
  new_var2 = ((s8 *) temp_3) + 0x290;
  new_var = 0;
  if ((*((u8 *) new_var2)) != new_var)
  {
    func_001880D8(temp_3 + 0x290);
  }
  func_00193988(arg0);
}
