#include "include_asm.h"
#include "ps2/prelude.h"

extern M2C_UNK D_003E1E78;
extern s32 func_002486D8();
extern s32 func_00387020();
extern s32 func_0024FA98();
extern void *D_0043DEE4;
extern s32 func_00251B38();
extern M2C_UNK D_003E1C40;
extern s32 func_00251D98();
extern M2C_UNK D_003E1B68;

void func_00251F70(void *arg0, s32 arg1)
{
  int new_var;
  *((M2C_UNK **) (((s8 *) arg0) + 4)) = &D_003E1E78;
  new_var = 0x30;
  func_002486D8(arg0 + 8, 2);
  if ((arg1 && arg1) && arg1)
  {
  }
 do { } while (0);
  func_00387020(arg0, 0);
  if (arg1 & 1)
  {
    func_0024FA98(D_0043DEE4, arg0, new_var);
  }
}

s32 func_00251FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00251B38(arg0, 0x2B, arg1, arg3, 1);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E1C40;
    return arg0;
}

s32 func_00252030(s32 arg0, s32 arg1, s32 arg2) {
    func_00251D98(arg0, 0x2B, arg1, arg2);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E1C40;
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(arg1, s32 *, 0x30);
    return arg0;
}

s32 func_00252088(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_00251B38(arg0, 0x2C, arg1, arg3, 1);
    M2C_FIELD(arg0, s32 *, 0x30) = arg2;
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E1B68;
    return arg0;
}

s32 func_002520D8(s32 arg0, s32 arg1, s32 arg2) {
    func_00251D98(arg0, 0x2C, arg1, arg2);
    M2C_FIELD(arg0, M2C_UNK **, 4) = &D_003E1B68;
    M2C_FIELD(arg0, s32 *, 0x30) = (s32) M2C_FIELD(arg1, s32 *, 0x30);
    return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00252190);
