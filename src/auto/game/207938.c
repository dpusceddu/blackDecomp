#include "auto/prelude.h"

extern s32 func_002050B0();
extern s32 func_00278F00();

s32 func_00207938(void *arg0)
{
  s8 *new_var;
  new_var = (s8 *) arg0;
  func_002050B0();
  func_00278F00(*((void **) (new_var + 8)), *((s32 *) (new_var + 0x64)), *((s32 *) (new_var + 0x7C)));
  return 1;
}
