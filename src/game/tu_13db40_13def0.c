#include "ps2/prelude.h"

extern s32 func_0013EE28();
extern void func_0013EE30();

s32 func_0013DEF0(void *arg0)
{
  s8 *new_var;
  func_0013EE28();
  ;
  M2C_FIELD(arg0, s8 *, 0xC1) = 1;
  M2C_FIELD(arg0, s8 *, 0xB9) = 0;
  M2C_FIELD(arg0, s8 *, 0xC0) = 0;
  M2C_FIELD(arg0, s32 *, 0xBC) = 0;
  M2C_FIELD(arg0, s32 *, 0x90) = 0;
  M2C_FIELD(arg0, s32 *, 0xC4) = 0;
  return 1;
}

void func_0013DF38(void) {
    func_0013EE30();
}
