#include "include_asm.h"
#include "ps2/prelude.h"

void func_0012D588(void *arg0)
{
  s8 *new_var;
  s8 *new_var2;
  M2C_FIELD(arg0, s32 *, 4) = -1;
  M2C_FIELD(arg0, s32 *, 0) = 1;
  new_var = (s8 *) arg0;
  *((s32 *) (new_var + 4)) = -1;
  M2C_FIELD(arg0, s32 *, 0) = 1;
  new_var2 = new_var;
  *((s32 *) (new_var2 + 0x6F4)) = 0;
  *((s32 *) (new_var + 8)) = -1;
  *((s8 *) (new_var + 0x38)) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_12d458_12d588", func_0012D5A8);
