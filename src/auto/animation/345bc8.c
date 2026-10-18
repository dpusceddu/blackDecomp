#include "auto/prelude.h"

extern s32 func_00343F48();
extern s32 func_00343F90();
extern s32 func_00349C38();

void func_00345BC8(void *arg0) {
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_2_3;

    if ((M2C_FIELD(arg0, s32 *, 0) & 0x480000) && (temp_2 = func_00343F48(M2C_FIELD(arg0, s16 *, 0x5E) << 7), M2C_FIELD(arg0, s32 *, 0x54) = temp_2, M2C_FIELD(arg0, s32 *, 0x50) = temp_2, (temp_2 != 0))) {
        temp_2_2 = M2C_FIELD(arg0, s32 *, 0) | 0x04000000;
        M2C_FIELD(arg0, s32 *, 0) = temp_2_2;
        if (temp_2_2 & 0x100000) {
            temp_2_3 = func_00343F48((M2C_FIELD(arg0, s16 *, 0x5E) << 7) + 0xC0);
            M2C_FIELD(arg0, s32 *, 0x68) = temp_2_3;
            if (temp_2_3 == 0) {
                func_00343F90(M2C_FIELD(arg0, s32 *, 0x54));
                return;
            }
            func_00349C38(temp_2_3, M2C_FIELD(arg0, s16 *, 0x5E));
            goto block_6;
        }
block_6:
        M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) & 0xFFF7FFFF);
    }
}

void func_00345C78(void *arg0)
{
  s32 temp_4;
  s32 temp_5;
  temp_5 = M2C_FIELD(arg0, s32 *, 0x68);
  M2C_FIELD(arg0, s32 *, 0) = (s32) (((M2C_FIELD(arg0, s32 *, 0)) | 0x80000) & 0xFFBFFFFF);
  if (temp_5 != 0)
  {
    func_00343F90(temp_5, temp_5);
    M2C_FIELD(arg0, s32 *, 0x68) = 0;
  }
  temp_4 = M2C_FIELD(arg0, s32 *, 0x54);
  if (temp_4 != 0)
  {
    func_00343F90(temp_4);
    M2C_FIELD(arg0, s32 *, 0x50) = (M2C_FIELD(arg0, s32 *, 0x54) = 0);
  }
}
