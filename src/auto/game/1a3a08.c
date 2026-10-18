#include "auto/prelude.h"

extern s32 func_001A24B8();
extern s32 func_00173690();
extern void func_00173658();

s32 func_001A3A08(void *arg0)
{
  func_001A24B8();
  func_00173690(arg0 + 0x78);
  M2C_FIELD(arg0, s32 *, 0x74) = 0;
  M2C_FIELD(arg0, s8 *, 0x88) = 7;
  func_00173658(arg0 + 0x84);
  return 1;
}
