#include "ps2/prelude.h"

extern s32 func_00281948();

void func_00280808(void *arg0)
{
  void *new_var3;
  int new_var2;
  void *new_var;
  new_var2 = 1;
  new_var = arg0;
  new_var3 = new_var + 0xB308;
  func_00281948(new_var3, new_var2);
  M2C_FIELD(new_var, s8 *, 0xCB9E) = new_var2;
}
