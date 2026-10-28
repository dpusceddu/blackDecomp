#include "include_asm.h"
#include "ps2/prelude.h"

extern void func_0013ED98(void* self);
extern s32 func_0013EC38(void* self, void* actor);
extern void* D_0040F0E0;
extern s128 D_004432A0;

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13db40_13def0", func_0013DF58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13db40_13def0", func_0013EB00);

void func_0013EC10(void* arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x80) = arg1;
    M2C_FIELD(arg0, s32 *, 0x7C) = 0;
    M2C_FIELD(arg0, s8 *, 0x78) = 0;
    func_0013ED98(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13db40_13def0", func_0013EC38);

void func_0013ED98(void* self) {
    M2C_FIELD(self, s32*, 0xC) = 0;
    M2C_FIELD(self, s32*, 8) = 0;
    M2C_FIELD(self, s32*, 0) = 0;
    M2C_FIELD(self, s32*, 4) = 0;
    M2C_FIELD(self, s32*, 0x10) = 0;
    M2C_FIELD(self, s128*, 0x50) = D_004432A0;
    M2C_FIELD(self, s128*, 0x60) = D_004432A0;
    M2C_FIELD(self, s128*, 0x20) = D_004432A0;
    M2C_FIELD(self, s8*, 0x3D) = 1;
    M2C_FIELD(self, s32*, 0x70) = 0;
    M2C_FIELD(self, s8*, 0x30) = 0;
    M2C_FIELD(self, s8*, 0x31) = 0;
    M2C_FIELD(self, s8*, 0x32) = 0;
    M2C_FIELD(self, s8*, 0x33) = 0;
    M2C_FIELD(self, s8*, 0x34) = 0;
    M2C_FIELD(self, s8*, 0x35) = 0;
    M2C_FIELD(self, s8*, 0x36) = 0;
    M2C_FIELD(self, s8*, 0x37) = 0;
    M2C_FIELD(self, s8*, 0x38) = 0;
    M2C_FIELD(self, s8*, 0x39) = 0;
    M2C_FIELD(self, s8*, 0x3B) = 0;
    M2C_FIELD(self, s8*, 0x3C) = 0;
    M2C_FIELD(self, s32*, 0x44) = 0;
    M2C_FIELD(self, s32*, 0x48) = 0;
    M2C_FIELD(self, s32*, 0x40) = 0;
    M2C_FIELD(self, s32*, 0x4C) = 0;
}

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_13db40_13def0", func_0013EF28);

void func_0013F0A8(void* self) {
    func_0013EC10(self, 0);
    M2C_FIELD(self, s32*, 0x98) = 0;
    M2C_FIELD(self, s8*, 0x9D) = 0;
}

s32 func_0013F0D8(void* self, s8 index, void* actor) {
    s32 base;
    s32 offset;

    if (M2C_FIELD(self, u8*, 0x9D)) return 1;

    func_0013EC38(self, actor);
    base = (s32)D_0040F0E0 + 0x21060;
    offset = index * 12;
    M2C_FIELD(self, void**, 0x98) = M2C_FIELD(base + offset, void**, 0);
    M2C_FIELD(self, s8*, 0x9C) = index;
    M2C_FIELD(self, u8*, 0x9D) = 1;
    return 1;
}
