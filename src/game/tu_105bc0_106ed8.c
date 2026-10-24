#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001536B0(s32);
extern s32 func_00105228();
extern void * D_0040F0E0;
extern s32 func_0026CA20();
extern s32 func_00274E68();
extern s32 func_00107AB8();
extern s32 func_00107B08();

void func_00106ED8(s32 arg0) {
    func_001536B0(arg0 + 0xC);
}

void func_00106EF8(void *arg0) {
    void *temp_5;
    void *temp_6;

    temp_5 = arg0 + 0xC;
    temp_6 = M2C_FIELD(arg0, void **, 0x48);
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) | 1);
    if ((s16) (M2C_FIELD(temp_5, u16 *, 0x14) - M2C_FIELD(temp_5, u16 *, 0x16)) >= (s32) M2C_FIELD(temp_6, u8 *, 0xF)) {
        func_00105228(D_0040F0E0 + 0x20220, 5, temp_6);
        return;
    }
    func_00105228(D_0040F0E0 + 0x20220, 4, temp_6);
}

void func_00106F80(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) | 2);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x48), u8 *, 0x35) != 0) {
        func_00105228(D_0040F0E0 + 0x20220, 5);
        return;
    }
    func_00105228(D_0040F0E0 + 0x20220, 4);
}

void func_00106FE8(void *arg0, s32 arg1, s64 arg2) {
    M2C_FIELD(arg0, s64 *, 0x28) = arg2;
    M2C_FIELD(arg0, s32 *, 0x38) = (s32) (M2C_FIELD(arg0, s32 *, 0x38) | 4);
}

void func_00107000(void *arg0, s64 arg1) {
    M2C_FIELD(arg0, s64 *, 0x30) = arg1;
}

s64 func_00107008(void *arg0) {
    return M2C_FIELD(arg0, s64 *, 0x30);
}

void func_00107010(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x778) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107020);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107470);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_001077B8(s32, s32, s32, f32, f32);
extern s32 func_00107800(s32, s32, s32, f32, f32, f32, f32);

s32 func_00107730(s32 arg0, s32 arg1, s8 arg2, s32 arg3, f32 fparg0, f32 fparg1, f32 fparg2, f32 fparg3) {
    s32 var_2;

    switch (arg1) {                                 /* irregular */
    case 0:
        var_2 = func_001077B8(arg0, (s32) arg2, arg3, fparg0, fparg1);
block_5:
        return var_2;
    case 1:
        var_2 = func_00107800(arg0, (s32) arg2, arg3, fparg0, fparg1, fparg2, fparg3);
        goto block_5;
    default:
        return 1;
    }
}

void func_00107788(s32 arg0, s32 arg1, f32 fparg0)
{
  int new_var;
  f32 *temp_4;
  new_var = arg0 + 0x78C;
  temp_4 = new_var + (((s32) (arg1 << 0x18)) >> 0x16);
  if ((*temp_4) < fparg0)
  {
    *temp_4 = fparg0;
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001077B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107800);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107878);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107880);

void func_001078D8(s32 arg0, s8 arg1) {
    M2C_FIELD((arg0 + arg1), s8 *, 0x79D) = 1;
}

s32 func_001078F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = func_0026CA20(arg0, arg1);
    M2C_FIELD(arg0, s8 *, 0x79C) = (s8) arg1;
    return temp_v0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107928);

void func_00107A00(void) {

}

s32 func_00107A08(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    M2C_FIELD(arg0, s32 *, 0x1C) = arg2;
    M2C_FIELD(arg0, s32 *, 0x20) = arg1;
    return func_00274E68(arg0, arg1, arg3);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00107A38);

s32 func_00107A40(s32 arg0)
{
  s32 temp_2;
  M2C_FIELD(arg0, s8 *, 0x3B8) = 1;
  M2C_FIELD(arg0, s32 *, 0x3AC) = 0;
  M2C_FIELD(arg0, s32 *, 0x3B4) = -1;
  temp_2 = func_00107AB8(arg0, 0, 0);
  M2C_FIELD(arg0, s8 *, 0) = 0;
  return temp_2;
}

s32 func_00107A88(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_00107B08(arg0, 0, 0);
    M2C_FIELD(arg0, s8 *, 0x3B8) = 0;
    return temp_v0;
}
