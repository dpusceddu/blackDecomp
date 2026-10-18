#include "auto/prelude.h"

extern s32 func_002A9140();

void func_001AE570(s32 arg0)
{
  int new_var;
  s32 *new_var2;
  new_var = arg0 + 0xD360;
  new_var2 = (s32 *) (((s8 *) new_var) + 0x58);
  func_002A9140(*new_var2, 0, 1);
}
