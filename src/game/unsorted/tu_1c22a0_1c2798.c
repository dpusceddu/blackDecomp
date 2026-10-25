#include "include_asm.h"
#include "ps2/prelude.h"

void func_001C2798(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2)
{
  s8 *new_var;
  s8 *new_var2;
  new_var2 = (s8 *) arg0;
  if ((M2C_FIELD(arg0, s32 *, 0x34)) == 0)
  {
    new_var = (s8 *) arg0;
    M2C_FIELD(arg0, f32 *, 0x24) = fparg2;
    *((s32 *) (new_var2 + 0x34)) = 1;
    *((f32 *) (new_var + 0x18)) = 1.0f;
    *((f32 *) (new_var + 0x1C)) = fparg0;
    *((s32 *) (new_var + 0x14)) = 0;
    *((f32 *) (new_var + 0x20)) = fparg1;
    *((s32 *) (new_var + 0x38)) = 0;
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2798", func_001C27D0);

void func_001C2838(void *arg0, f32 fparg0, f32 fparg1, f32 fparg2) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x34);
    if (temp_3 != 9) {
        M2C_FIELD(arg0, f32 *, 0x30) = fparg2;
        M2C_FIELD(arg0, s32 *, 0x38) = temp_3;
        M2C_FIELD(arg0, s32 *, 0x34) = 2;
        M2C_FIELD(arg0, f32 *, 0x18) = 1.0f;
        M2C_FIELD(arg0, f32 *, 0x28) = fparg0;
        M2C_FIELD(arg0, f32 *, 0x2C) = fparg1;
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2798", func_001C2878);

s32 func_001C28A0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x34) == 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c22a0_1c2798", func_001C28B0);
