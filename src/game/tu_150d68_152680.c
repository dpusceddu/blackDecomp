#include "ps2/prelude.h"

void func_00152680(void *arg0)
{
  long new_var;
  new_var = 0xFFFF;
  M2C_FIELD(arg0, s16 *, 0x1BC) = new_var;
}

s32 func_00152690(void) {
    return 0;
}
