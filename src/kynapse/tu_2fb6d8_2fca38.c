#include "ps2/prelude.h"

#include "types_ghidra.h"
extern M2C_UNK D_004536D0;

s32 func_002FCA38(s32 *arg0, s32 *arg1)
{
  f32 temp_f0;
  f32 temp_f1;
  s32 var_2;
  temp_f1 = *((f32 *) (((s8 *) (((*arg0) * 4) + ((s32) (&D_004536D0)))) + 0));
  temp_f0 = *((f32 *) (((s8 *) (((*arg1) * 4) + ((s32) (&D_004536D0)))) + 0));
 do { var_2 = -1; if (!(temp_f1 < temp_f0)) { var_2 = 1; if (!(temp_f0 < temp_f1)) { if (temp_f0 && temp_f0) { } return 0; } } } while (0);
  return var_2;
}
