#include "auto/prelude.h"

extern s32 func_00382348();
extern M2C_UNK D_00414D70;

void func_00158F08(void *arg0)
{
  func_00382348(&D_00414D70, 0x02B9D6F8);
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
 do { M2C_FIELD(arg0, s16 *, 0x18) = 0; } while (0);
  M2C_FIELD(arg0, s32 *, 0x14) = 0;
  M2C_FIELD(arg0, s8 *, 0x20) = 0;
}
