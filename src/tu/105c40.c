#include "auto/prelude.h"

extern void *D_0040F4C0;
extern s32 func_0035C6EC();
extern s32 func_002A9108();
extern s32 func_001C4FB0();
extern s32 func_0020B170();
extern s32 D_0040F544;
extern s32 func_001C50E0();
extern s32 func_001E8900(s32);
extern void * D_0040F510;

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
