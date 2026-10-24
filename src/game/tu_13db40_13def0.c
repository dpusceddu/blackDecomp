#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0013ED98();

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013DF58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013EB00);

s32 func_0013EC10(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x80) = arg1;
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
    M2C_FIELD(arg0, s8 *, 0x78) = 0;
    return func_0013ED98(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013EC38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013ED98);

void func_0013EE20(void) {

}

s32 func_0013EE28(void) {
    return 1;
}

void func_0013EE30(void) {

}

void func_0013EE38(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x78) = 1;
}

void func_0013EE48(void *arg0) {
    M2C_FIELD(arg0, s8 *, 0x78) = 0;
}

void func_0013EE50(void) {

}

void func_0013EE58(void) {

}

void func_0013EE60(void) {

}

f32 func_0013EE68(void *arg0) {
    f32 var_f3;

    var_f3 = M2C_FIELD(arg0, f32 *, 0) - M2C_FIELD(arg0, f32 *, 4);
    if (var_f3 < -180.0f) {
        var_f3 += 360.0f;
    } else if (var_f3 > 180.0f) {
        var_f3 -= 360.0f;
    }
    if (M2C_FIELD(arg0, f32 *, 0x74) > 0.01f) {
        var_f3 -= 5.0f;
    }
    return var_f3;
}

f32 func_0013EF08(void *arg0) {
    return M2C_FIELD(arg0, f32 *, 0xC);
}

void func_0013EF10(void *arg0, s128 arg1, s32 arg2) {
    M2C_FIELD(arg0, s128 *, 0x50) = arg1;
    if (arg2 != 0) {
        M2C_FIELD(arg0, s128 *, 0x60) = arg1;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013EF28);

s32 func_0013F0A8(s32 arg0)
{
  s32 temp_v0;
  if (1)
  {
    temp_v0 = func_0013EC10(arg0, 0);
  }
  M2C_FIELD(arg0, s8 *, 0x9D) = (M2C_FIELD(arg0, s32 *, 0x98) = 0);
  return temp_v0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013F0D8);
