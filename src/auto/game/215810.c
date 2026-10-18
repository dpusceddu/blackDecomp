#include "auto/prelude.h"

extern void func_00105258();
extern void *D_0040F0E0;
extern s32 func_0010B2C0();
extern s32 D_0040F4F0;
extern s32 D_003BE84C;

void func_00215810(void)
{
  void *new_var;
  void *new_var2;
  new_var2 = D_0040F0E0;
  new_var = new_var2 + 0x20220;
  func_00105258(new_var);
  func_0010B2C0(D_0040F4F0, 0);
  D_003BE84C = 5;
}
