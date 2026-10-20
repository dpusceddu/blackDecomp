#include "auto/prelude.h"
#include "mod/camera/vitals.h"

extern s32 func_001F2A60();
extern s32 D_0040F51C;
extern s32 D_0040F544;
extern s32 func_0021A7E0();
extern M2C_UNK D_003F49D8;
extern s32 func_0024F7D0();

s32 func_0013CD20(BkModPlayerVitalsPS2 *arg0)
{
  s32 temp_16;
  s8 temp_4;
  if (arg0->medkitCount == 3)
  {
    func_001F2A60(D_0040F51C, 0x35, 0, 0, 1);
    return 0;
  }
  temp_4 = (M2C_FIELD(arg0, s8 *, 0x8A1) = ((u8) arg0->medkitCount) + 1);
  temp_16 = D_0040F544 + 0x38C9;
  func_0021A7E0(&D_003F49D8, 0, temp_16, 1, func_0024F7D0(temp_4, arg0));
  if (func_001F2A60(D_0040F51C, 0xD, 1, 0, 1) == 0)
  {
    func_001F2A60(D_0040F51C, 0x13, 1, 0, 1);
  }
  return 1;
}
