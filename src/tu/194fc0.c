#include "auto/prelude.h"

extern s32 func_00193988();
extern s32 func_001880D8();
extern s32 func_00181028();
extern s32 func_00180FE0();
extern s32 func_00193990();

void func_00194FC0(void **arg0)
{
  void *temp_3;
  u8 *new_var;
  func_00193988();
  temp_3 = *arg0;
  new_var = &(M2C_FIELD(temp_3, u8 *, 0x290));
  if ((*new_var) != 0)
  {
    func_001880D8(temp_3 + 0x290);
  }
  if (func_00181028((*arg0) + 0x140) != 0)
  {
    func_00180FE0((*arg0) + 0x140);
  }
}

s32 func_00195020(s32 arg0) {
    return func_00193990(arg0, 0);
}
