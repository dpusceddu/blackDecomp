#include "include_asm.h"
#include "ps2/prelude.h"

void func_001C2A48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0) = 0x70002000;
    M2C_FIELD(arg0, s32 *, 4) = 0x70002800;
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2A68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2A98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2AB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2C50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2D90);

s32 func_001C2E30(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x428) = 0;
    return 1;
}

s32 func_001C2E40(void *arg0, void *arg1)
{
  f32 new_var;
  void *new_var2;
  s32 var_2;
  new_var = M2C_FIELD(arg0, f32 *, 4);
  var_2 = -1;
  new_var2 = arg1;
  if (!((M2C_FIELD(new_var2, f32 *, 4)) < new_var))
  {
    var_2 = 1;
  }
  return var_2;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2E68);

void func_001C2EA8(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C2EB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C3020);

s128 func_001C31E0(s128 **arg0) {
    return **arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C31F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C31F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C3228);
