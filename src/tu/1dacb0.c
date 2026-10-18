#include "auto/prelude.h"

extern s32 func_00284298(s32);
extern s32 func_002842E8(s32);

void func_001DACB0(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0xFA) = 0;
    M2C_FIELD(arg0, s8 *, 0xFB) = 0;
    M2C_FIELD(arg0, s8 *, 0xFC) = 0;
    func_00284298(M2C_FIELD(arg0, s32 *, 0xB0));
}

s32 func_001DACE0(void *arg0) {
    s32 temp_4;
    s32 var_2;

    temp_4 = M2C_FIELD(arg0, s32 *, 0xB0);
    var_2 = 0;
    if (temp_4 != 0) {
        var_2 = func_002842E8(temp_4);
    }
    return var_2;
}

s32 func_001DAD08(void *arg0)
{
  int new_var;
  s32 temp_5;
  s32 var_3;
  var_3 = 0;
  if (((u32) ((M2C_FIELD(arg0, s32 *, 0xB4)) - 6)) < 4U)
  {
    temp_5 = M2C_FIELD(arg0, s32 *, 0xF0);
    if (temp_5 >= 2)
    {
      var_3 = ((((s32) (temp_5 + (((u32) temp_5) >> 0x1F))) >> 1) * (new_var = 2)) * (M2C_FIELD(arg0, s32 *, 0xE0));
    }
    if ((M2C_FIELD(arg0, s32 *, 0xB0)) != 0)
    {
      var_3 += M2C_FIELD(arg0, s32 *, 0xE8);
    }
  }
  return var_3;
}

void func_001DAD60(void *arg0, s32 arg1) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0xA8);
    if (arg1 != 0) {
        M2C_FIELD(temp_4, s32 *, 0x54) = (s32) (M2C_FIELD(temp_4, s32 *, 0x54) | 2);
        return;
    }
    M2C_FIELD(temp_4, s32 *, 0x54) = (s32) (M2C_FIELD(temp_4, s32 *, 0x54) & 0xFFFFFFFD);
}
