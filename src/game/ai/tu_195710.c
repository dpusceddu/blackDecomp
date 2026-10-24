#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00193988();
extern s32 func_001880D8();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00195710);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00195860);

void func_001958E0(void **arg0)
{
  int new_var2;
  void *temp_3;
  int new_var;
  func_00193988();
  new_var = 0;
  new_var2 = 0x290;
  temp_3 = *arg0;
  if ((*((u8 *) (temp_3 + new_var2))) != new_var)
  {
    func_001880D8(temp_3 + new_var2);
  }
}

void func_00195920(void *arg0) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0xC);
    if ((temp_3 != 0) && (temp_3 != M2C_FIELD(arg0, s32 *, 8))) {
        M2C_FIELD(arg0, s32 *, 8) = temp_3;
    }
}
