#include "auto/prelude.h"

extern s32 func_0025DD38();
extern s32 func_00107B78();
extern M2C_UNK D_0040F0F0;
extern s32 func_00107D20();
extern s32 func_00135570();
extern void * D_0040F4D0;
extern s32 func_0025E2D0();
extern s32 func_0032B6E0();
extern s32 func_002611D0();

void func_00260C18(void *arg0)
{
  int new_var;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  M2C_FIELD(arg0, s32 *, 4) = 0;
 do { M2C_FIELD(arg0, s32 *, 0x14) = 0; func_0025DD38(); func_00107B78(&D_0040F0F0, 0xB, 0x10, 0); M2C_FIELD(arg0, s32 *, 0xC) = func_00107D20(0x750); } while (0);
  new_var = 0x10;
  *((s8 *) (((s8 *) arg0) + new_var)) = 0;
  arg0++;
  arg0--;
}

s32 func_00260C70(void *arg0, s32 arg1) {
    s32 temp_2;

    M2C_FIELD(arg0, s32 *, 0) = arg1;
    temp_2 = func_00135570(arg1);
    M2C_FIELD(arg0, s32 *, 4) = temp_2;
    M2C_FIELD(arg0, f32 *, 0x14) = (f32) M2C_FIELD(D_0040F4D0, f32 *, 0x20);
    if (M2C_FIELD(arg0, u8 *, 0x10) == 0) {
        M2C_FIELD(arg0, u8 *, 0x10) = 1U;
        func_0025E2D0(arg0, temp_2);
    }
    func_0032B6E0(M2C_FIELD(arg0, void **, 0xC), M2C_FIELD(arg0, s32 *, 8));
    M2C_FIELD(M2C_FIELD(arg0, void **, 0xC), s32 *, 0x18) = 7;
    func_002611D0(arg0);
    M2C_FIELD(arg0, s8 *, 0x18) = 0;
    return 1;
}
