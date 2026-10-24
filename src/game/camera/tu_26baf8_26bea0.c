#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0026BAF8();
extern s32 func_0029CB50();

void func_0026BEA0(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xE8) != 0) {
        M2C_FIELD(arg0, s32 *, 0xE8) = 0;
        M2C_FIELD(arg0, s32 *, 0xEC) = -1;
    }
}

f32 func_0026BEC0(void *arg0, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 var_f12;
    f32 var_f12_2;

    var_f12_2 = fparg0;
    temp_f1 = M2C_FIELD(arg0, f32 *, 0xD0);
    if (temp_f1 < var_f12_2) {
        var_f12_2 = temp_f1;
    }
    temp_f0 = M2C_FIELD(arg0, f32 *, 0xD4);
    var_f12 = var_f12_2 - temp_f0;
    if (var_f12 < 0.0f) {
        var_f12 = 0.0f;
    }
    return var_f12 * (1.0f / (temp_f1 - temp_f0));
}

f32 func_0026BF10(void *arg0, f32 fparg0) {
    f32 temp_f0;
    f32 temp_f1;
    f32 var_f12;
    f32 var_f12_2;

    var_f12_2 = fparg0;
    temp_f1 = M2C_FIELD(arg0, f32 *, 0xD8);
    if (temp_f1 < var_f12_2) {
        var_f12_2 = temp_f1;
    }
    temp_f0 = M2C_FIELD(arg0, f32 *, 0xDC);
    var_f12 = var_f12_2 - temp_f0;
    if (var_f12 < 0.0f) {
        var_f12 = 0.0f;
    }
    return var_f12 * (1.0f / (temp_f1 - temp_f0));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0026BF60);

s32 func_0026BFF0(void *arg0)
{
  void *new_var;
  new_var = arg0;
  if (func_0026BAF8() != 0)
  {
    if (new_var || arg0)
    {
      *((s32 *) (((s8 *) new_var) - -4)) = 4;
      return 1;
    }
    else
    {
      *((s32 *) (((s8 *) new_var) - -4)) = 4;
      return 1;
    }
  }
  return 0;
}

void func_0026C030(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s8 *new_var;
  *((f32 *) (new_var = ((s8 *) (arg0 + (arg1 * 4))) + 0x4C)) = func_0026BEC0(arg0, ((f32) func_0029CB50(arg3, arg4)) / 255.0f);
}

void func_0026C098(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s8 *new_var;
  *((f32 *) (new_var = ((s8 *) (arg0 + (arg1 * 4))) + 0x4C)) = func_0026BF10(arg0, ((f32) func_0029CB50(arg3, arg4)) / 255.0f);
}
