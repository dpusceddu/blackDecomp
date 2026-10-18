#include "auto/prelude.h"

extern s32 func_00319480();
extern s32 D_00458480;
extern s32 func_00319928();
extern s32 func_00324948();
extern void func_003249E8();

void func_00319410(void *arg0)
{
  int new_var;
  void *new_var2;
  s32 temp_4;
  func_00319480();
  new_var2 = arg0 + 4;
  temp_4 = new_var2;
  new_var = D_00458480 == temp_4;
  if (new_var)
  {
    func_00319928(temp_4);
  }
  if (((*(*((s32 **) (((s8 *) arg0) + 0)))) == 2) && (func_00324948(M2C_FIELD(arg0, s32 *, 0x5C)) != 0))
  {
    func_003249E8(M2C_FIELD(arg0, s32 *, 0x5C));
    M2C_FIELD(arg0, s32 *, 0x5C) = 0;
  }
}
