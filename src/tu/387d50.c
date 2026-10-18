#include "auto/prelude.h"
#include "types_ghidra.h"

extern M2C_UNK D_003E2450;
extern s32 func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern void *D_0043DEE4;

void func_00387D50(void *arg0, s32 arg1)
{
  s32 new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E2450;
  new_var = arg1;
  do
  {
    *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E2450;
 do { func_002486D8(arg0 + 8, 2); } while (0);
  }
  while (0);
  func_00387020(arg0, 0);
  if ((new_var & 1) != 0U)
  {
    func_0024FA98(D_0043DEE4, arg0, 0x20);
  }
}

s32 func_00387DC0(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_4 < M2C_FIELD(arg0, s32 *, 0)) {
        temp_2_2 = M2C_FIELD(arg0, s32 *, 8);
        M2C_FIELD(((temp_4 * 4) + temp_2_2), s32 *, 0) = arg1;
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_4 + 1);
        return temp_2_2;
    }
    temp_2 = M2C_FIELD(arg1, s32 *, 0) & ~4;
    M2C_FIELD(arg1, s32 *, 0) = temp_2;
    return temp_2;
}
