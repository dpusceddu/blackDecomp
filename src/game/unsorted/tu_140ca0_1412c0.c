#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001735E0(s32);

s32 func_001412C0(void *arg0)
{
  int new_var;
  s32 temp_3;
  temp_3 = *((s32 *) (((s8 *) arg0) + (0x4B4 ^ 0)));
  if (temp_3 != (-1))
  {
    new_var = temp_3 * 4;
    return *((s32 *) (((s8 *) (arg0 + new_var)) + 0x490));
  }
  if (temp_3 || arg0)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}

void func_001412E8(void *arg0, s32 arg1)
{
  s8 *new_var;
  s32 temp_3;
  temp_3 = M2C_FIELD(arg0, s32 *, 0x4DC);
  new_var = ((s8 *) (arg0 + (temp_3 * 4))) + 0x4B8;
  *((s32 *) new_var) = arg1;
  M2C_FIELD(arg0, s32 *, 0x4DC) = (s32) (temp_3 + 1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00141308);

#include "ps2/recovered_types.h"
extern s32 func_00173640(f32 *, f32);

s32 func_00141418(void *arg0) {
    return func_00173640(arg0 + 0x4E0, 2.0f);
}

void func_00141440(s32 arg0) {
    func_001735E0(arg0 + 0x4E0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00141460);

u8 func_00141490(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x4E5);
}

u8 func_00141498(void *arg0) {
    return M2C_FIELD(arg0, u8 *, 0x4E4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001414A0);
