#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0030F678();
extern s32 func_0030FD68();

s32 func_003100A0(s32 arg0)
{
  M2C_FIELD(arg0, s8 *, 0x48) = 0;
  M2C_FIELD(arg0, s32 *, 0x28) = 0;
  M2C_FIELD(arg0, s8 *, 0x52) = 1;
  arg0++;
  arg0--;
  M2C_FIELD(arg0, s8 *, 0x49) = 1;
  func_0030F678(arg0);
  return M2C_FIELD(arg0, s32 *, 0x28);
}

void func_00310228(void) {
    func_0030FD68(1, 0xFFFF);
}

void func_00310248(void) {
    func_0030FD68(0, 0xFFFF);
}

