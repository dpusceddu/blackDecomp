#include "auto/prelude.h"

extern void *func_0031E4C0();
extern s32 func_00316668();
extern s32 func_00317C20();
extern M2C_UNK *D_00458768;
extern M2C_UNK *D_00458740;
extern M2C_UNK *D_00458718;

void func_0031E428(M2C_UNK *arg0)
{
  s32 temp_3;
  s32 var_2;
  func_0031E4C0();
  func_00316668(arg0);
  temp_3 = M2C_FIELD(arg0, s32 *, 0xC);
  if (temp_3 & 8)
  {
    var_2 = temp_3 & 4;
    if (!(temp_3 & 0x20))
    {
      func_00317C20(&D_00458768, *((M2C_UNK **) (((s8 *) arg0) + 0x50)));
      goto block_3;
    }
  }
  else
  {
  }
  block_3:
  var_2 = (M2C_FIELD(arg0, s32 *, 0xC)) & 4;

  if ((var_2 != 0) && (!((M2C_FIELD(arg0, s32 *, 0xC)) & 0x10)))
  {
    func_00317C20(&D_00458740, *((M2C_UNK **) (((s8 *) arg0) + 0x4C)));
  }
  if ((M2C_FIELD(arg0, s32 *, 0xC)) & 2)
  {
    func_00317C20(&D_00458718, arg0);
  }
}
