#include "auto/prelude.h"

extern s32 func_00280A80();
extern void func_001D7128();
extern s32 func_001F0620();
extern s32 func_001F0770(s32, f32);
extern f32 D_003BD2A8;

void func_001D6C48(void *arg0)
{
  int temp_4;
  M2C_FIELD(arg0, s32 *, 0x1C24) = (s32) (((M2C_FIELD(arg0, s32 *, 0x1C24)) + 1) ^ 0);
  M2C_FIELD(arg0, s32 *, 0x1C40) = (s32) ((M2C_FIELD(arg0, s32 *, 0x1C40)) - 1);
  func_00280A80(arg0 + 0x40);
  if (((!D_003BD2A8) && (!D_003BD2A8)) && (!D_003BD2A8))
  {
    if (arg0)
    {
    }
  }
  func_001D7128(arg0);
  temp_4 = M2C_FIELD(arg0, s32 *, 0x1BE0);
  if (temp_4 != 0)
  {
    func_001F0620(temp_4, M2C_FIELD(arg0, s32 *, 0x1C24));
    func_001F0770(M2C_FIELD(arg0, s32 *, 0x1BE0), D_003BD2A8);
  }
}
