#include "ps2/prelude.h"

extern M2C_UNK D_003E1E78;
extern s32 func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern s32 D_0043DEE4;

void func_003861F8(void *arg0, s32 arg1)
{
  s32 *new_var;
  *((M2C_UNK **) (((s8 *) arg0) + ((unsigned short) 4))) = &D_003E1E78;
  func_002486D8(arg0 + 8, 2);
  new_var = &D_0043DEE4;
 do { } while (0);
  func_00387020(arg0, 0);
  if (arg1 & 1)
  {
    func_0024FA98(*new_var, arg0, 0x2C);
  }
}
