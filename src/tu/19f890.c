#include "auto/prelude.h"

extern s32 func_00193980();
extern s32 func_00187FE0(s32, M2C_UNK);
extern s32 func_00173690(void **);
extern s32 func_0019FA98(void *);
extern s32 func_0019F9D8(void *);
extern s32 func_00193988();
extern s32 func_001880D8();

void func_0019F890(void *arg0) {
    func_00193980();
    func_00187FE0(M2C_FIELD(arg0, void **, 0) + 0x290, 0);
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x694), s8 *, 0x30) = 0;
    func_00173690(arg0 + 0x24);
    M2C_FIELD(arg0, s8 *, 0x28) = 0;
    M2C_FIELD(arg0, s8 *, 0x21) = 0;
    func_0019FA98(arg0);
    func_0019F9D8(arg0);
}

void func_0019F8F0(void **arg0)
{
  int new_var2;
  void *temp_3;
  int new_var;
  func_00193988();
  new_var = 0;
  new_var2 = 0x290;
  temp_3 = *arg0;
  if ((*((u8 *) (temp_3 + new_var2))) != new_var)
  {
    func_001880D8(temp_3 + new_var2);
  }
}
