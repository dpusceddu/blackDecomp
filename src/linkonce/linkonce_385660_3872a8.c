#include "auto/prelude.h"

extern u16 D_003BFAF8;
extern s32 func_00253FF0();
extern s32 func_00250198();
extern s32 D_0043DEE0;
extern s32 func_00107D48();

s32 func_003872A8(s32 *arg0) {
    return *arg0 == (s32) &D_003BFAF8;
}

u16 ** func_003872C0(u16 **arg0) {
    *arg0 = &D_003BFAF8;
    D_003BFAF8 += 1;
    return arg0;
}

s32 func_003872E0(s32 arg0) {
    func_00253FF0();
    return arg0;
}

u16 ** func_00387308(u16 **arg0, u16 **arg1) {
    u16 *temp_6;

    temp_6 = *arg1;
    *arg0 = temp_6;
    *temp_6 += 1;
    return arg0;
}

void func_00387328(u16 **arg0, s32 arg1)
{
  u16 *temp_5;
  u16 temp_2;
  int new_var2;
  s8 *new_var;
  new_var2 = 4;
  temp_5 = *arg0;
  new_var = (s8 *) temp_5;
  temp_2 = (*((u16 *) (new_var + 0)) = (0, (*((u16 *) (new_var + 0))) - 1));
  if (!(temp_2 & 0xFFFF))
  {
    temp_2 = *((u16 *) (new_var + new_var2));
    func_00250198(D_0043DEE0, temp_5, temp_2 + 9);
  }
  if (arg1 & 1)
  {
    func_00107D48(arg0);
  }
}
