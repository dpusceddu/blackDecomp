#include "ps2/prelude.h"

const u32 rodata_003F4228[14] __asm__("D_003F4228") __attribute__((aligned(8))) = { 0x00000032, 0x00000078, 0x0000008C, 0x00000082, 0x0000007D, 0x0000006E, 0x00000064, 0x00000096, 0x3F800000, 0x3E99999A, 0x3F800000, 0x3F19999A, 0x3F800000, 0x00000000 };
extern volatile char D_003F4228;
extern void func_00122BB0(s32);
extern s32 * D_0040F53C;
extern void func_00122BD0(s32);
extern s32 func_00122BF0();
extern s32 func_00122C20();
extern s32 func_00122C50();

s32 func_001229F8(void) {
    return 8;
}

s32 func_00122A00(s32 arg0, s32 arg1)
{
  M2C_UNK *new_var;
  new_var = &(*((((s32) (arg1 << 0x18)) >> 0x16) + (&D_003F4228)));
  return *new_var;
}

void func_00122A20(void) {
    func_00122BB0(*D_0040F53C);
}

void func_00122A48(void) {
    func_00122BD0(*D_0040F53C);
}

void func_00122A70(void) {
    func_00122BF0(*D_0040F53C);
}

void func_00122A98(void) {
    func_00122C20(*D_0040F53C);
}

void func_00122AC0(void) {
    func_00122C50(*D_0040F53C);
}
