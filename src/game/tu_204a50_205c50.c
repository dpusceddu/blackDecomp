#include "ps2/prelude.h"

extern s32 func_00204F00();
extern s32 func_00206A28();
extern s32 func_00206B58();

void func_00205C50(void *arg0)
{
  int new_var2;
  void *new_var;
  func_00204F00();
  func_00206A28(arg0 + 0x60, arg0);
  func_00206B58(arg0 + 0x88, arg0);
  new_var2 = 1;
  M2C_FIELD(arg0, s8 *, 0xC9) = (long) 0;
  M2C_FIELD(arg0, s8 *, 0xD0) = new_var2;
  new_var = arg0;
  M2C_FIELD(new_var, s8 *, 0xCA) = 0;
}
