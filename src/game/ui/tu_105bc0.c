#include "include_asm.h"
#include "ps2/prelude.h"

extern void *D_0040F4C0;
extern s32 func_0035C6EC();
extern s32 func_002A9108();
extern s32 func_001C4FB0();
extern s32 func_0020B170();
extern s32 D_0040F544;
extern s32 func_001C50E0();
extern s32 func_001E8900(s32);
extern void * D_0040F510;
extern void * D_0040F0E0;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00105BC0);

void func_00105C40(void)
{
  u8 sp[8];
  s8 *new_var;
  void *temp_16;
  temp_16 = D_0040F4C0 + 0xD360;
  func_0035C6EC(sp, 0, 4);
  func_002A9108(*((s32 *) (new_var = ((s8 *) temp_16) + 0x58)), sp, 3);
  func_001C4FB0(D_0040F4C0, 0);
  D_0040F4C0 += 0;
  func_0020B170(D_0040F544);
  func_001C50E0(D_0040F4C0);
}

s32 func_00105CB8(void) {
    return func_001E8900(M2C_FIELD(D_0040F510, s32 *, 0xCBD8)) != 0;
}

void func_00105CE8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00105CF0);

void func_00106008(void) {

}

s32 func_00106010(void) {
    M2C_FIELD(D_0040F0E0, s32 *, 0x20208) = 2;
    M2C_FIELD(D_0040F0E0, s8 *, 0x2020C) = 0;
    M2C_FIELD(D_0040F0E0, s8 *, 0x2020D) = 0;
    return 1;
}

void func_00106048(void) {

}

void func_00106050(void) {

}

s32 func_00106058(void) {
    return 1;
}

void func_00106060(void) {

}
