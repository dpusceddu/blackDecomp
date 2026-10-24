#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_00143590();

s32 func_00135C78(void *arg0, s32 arg1, s32 arg2, s32 arg3)
{
  s8 *new_var;
  new_var = ((s8 *) (arg0 + (arg1 * 4))) + 0x25C;
  func_00143590(*((void **) new_var), arg2, arg3 & 0xFF);
  M2C_FIELD(arg0, s8 *, 0x3AD) = 1;
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00135CC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00135CC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00135D30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00135DD8);

void func_00135E28(void *arg0, s32 arg1) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0x3A0);
    if (temp_3 != 3) {
        if ((u32) (arg1 - 2) < 2U) {
            M2C_FIELD(arg0, s32 *, 0x3A0) = 2;
            return;
        }
        if ((temp_3 == 0) && (arg1 == 1)) {
            M2C_FIELD(arg0, s32 *, 0x3A0) = arg1;
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00135E68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00135EA0);

void func_00135EA8(void *arg0, f32 fparg0, f32 fparg1) {
    if (M2C_FIELD(arg0, u8 *, 0x3B7) == 0) {
        M2C_FIELD(arg0, f32 *, 0x310) = fparg0;
        M2C_FIELD(arg0, f32 *, 0x314) = fparg1;
        M2C_FIELD(arg0, s8 *, 0x3B5) = 1;
        M2C_FIELD(arg0, s8 *, 0x3B4) = 0;
    }
}
