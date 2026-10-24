#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern M2C_UNK D_003BCDF8;

u8 func_0012FC78(s32 arg0, u32 arg1, u32 arg2)
{
  s32 temp_4;
  int new_var;
  new_var = 0x1F;
  temp_4 = ((s32) ((arg2 >> new_var) + arg2)) >> 1;
  if (((arg1 >= 9U) || (temp_4 >= 8)) || (temp_4 < 0))
  {
    return 0U;
  }
  new_var = temp_4 + (arg1 * 8);
  return *((u8 *) (((s8 *) (new_var + ((s32) (&D_003BCDF8)))) + 0));
}
