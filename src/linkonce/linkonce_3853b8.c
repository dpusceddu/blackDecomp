#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00387E28();
extern M2C_UNK D_003FCD70;
extern void func_00385458();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003853B8);

s32 func_003853F8(void *arg0, s32 arg1, s32 arg2, void *arg3)
{
  int new_var;
  if (!func_00387E28(arg2, &D_003FCD70))
  {
    new_var = 0;
    return new_var;
    do
    {
    }
    while (new_var);
  }
  func_00385458(arg0, arg3);
  return 1;
}

s32 func_00385450(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x1C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00385458);
