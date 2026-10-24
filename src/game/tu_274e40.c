#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 D_003C09E0;
extern void func_00274F08();
extern s32 (*D_00449544)();

s32 func_00274E40(s32 arg0) {
    M2C_FIELD(arg0, s32 *, 4) = 0;
    M2C_FIELD(arg0, s8 *, 0) = 0;
    return func_00274F58(arg0, 4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274E68);

void func_00274EA8(void *arg0)
{
  s32 temp_4;
  int new_var2;
  s32 *new_var;
  new_var = (s32 *) (((s8 *) arg0) + 4);
  if (arg0 == D_003C09E0)
  {
    func_00274F08();
  }
  temp_4 = *new_var;
  if (temp_4 != 0)
  {
    new_var2 = 4;
    D_00449544(temp_4);
    *((s32 *) (((s8 *) arg0) + new_var2)) = 0;
  }
 do { M2C_FIELD(arg0, s8 *, 0) = 0; M2C_FIELD(arg0, s32 *, 8) = 0; } while (0);
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00274F08);

void func_00274F58(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x14) = arg1;
}

s32 func_00274F60(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 8);
}

s32 func_00274F70(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0xC) - M2C_FIELD(arg0, s32 *, 0x10);
}
