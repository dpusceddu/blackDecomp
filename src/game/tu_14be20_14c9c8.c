#include "auto/prelude.h"

extern s32 func_00274E40();
extern s32 func_00274E68();
extern void *func_00107D20();
extern s32 func_00274F58();
extern s32 func_00343F38();

void func_0014C9C8(void *arg0, s32 arg1)
{
  s32 temp_17;
  temp_17 = arg0 + 4;
  M2C_FIELD(arg0, s32 *, 0x28) = 0x20 * 0;
  func_00274E40(temp_17);
  func_00274E68(temp_17, func_00107D20(arg1), arg1);
 do { } while (0);
  func_00274F58(temp_17, 0x10);
  M2C_FIELD(arg0, s32 *, 0x20) = func_00343F38();
}
