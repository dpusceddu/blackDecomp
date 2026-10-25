#include "include_asm.h"
#include "ps2/prelude.h"

extern f32 func_00118210();

void func_00118078(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x54) = 0;
}

void func_00118080(void) {

}

s32 func_00118088(void) {
    return 1;
}

void func_00118090(void *arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
}

s32 func_00118098(void)
{
  s32 var_2;
  f32 new_var;
  new_var = func_00118210();
  var_2 = 1;
  if (!(new_var >= 1.0f))
  {
    var_2 = 0;
  }
  return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_116f60_118078", func_001180D8);
