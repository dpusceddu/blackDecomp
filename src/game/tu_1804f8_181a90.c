#include "auto/prelude.h"

extern s32 func_00181990();
extern s32 func_0018BE88();
extern s32 func_00181B08();

void *func_00181A90(void *arg0, s32 arg1)
{
  void *new_var;
  if (arg1 != 0x4A)
  {
    new_var = (s8 *) (arg0 + ((2 * arg1) * 2));
    return *((void **) (0x718 + new_var));
  }
  if (arg1 || arg0)
  {
    new_var = (void *) 0;
    return (void *) 0;
  }
  else
  {
    return new_var;
  }
}

void func_00181AB0(void) {
    func_00181990();
}

void func_00181AD0(void *arg0, s32 arg1) {
    u8 sp[8];
    if (arg1 != 0) {
        func_0018BE88(sp);
        func_00181B08(arg0, sp);
    }
}
