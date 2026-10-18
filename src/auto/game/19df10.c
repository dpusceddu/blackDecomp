#include "auto/prelude.h"

extern s32 func_00193988();
extern s32 func_001880D8();
extern s32 func_001823B0();
extern s32 func_001829A8();
extern s32 func_001829E8();

void func_0019DF10(void **arg0)
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

s32 func_0019DF50(void *arg0) {
    if (M2C_FIELD(arg0, u8 *, 0x44) != 0) {
        M2C_FIELD(arg0, s8 *, 0x45) = 0;
        return 1;
    }
    M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0x694), s8 *, 0x30) = 0;
    if ((func_001823B0(M2C_FIELD(arg0, void **, 0) + 0x810, M2C_FIELD(arg0, s128 *, 0x10), 0) == 0) || (func_001829A8(M2C_FIELD(arg0, void **, 0) + 0x810) == 0) || (func_001829E8(M2C_FIELD(arg0, void **, 0) + 0x810) != 0)) {
        M2C_FIELD(arg0, s8 *, 0x45) = 0;
        M2C_FIELD(arg0, u8 *, 0x44) = 1U;
        return 1;
    }
    return 0;
}
