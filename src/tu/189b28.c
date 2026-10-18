#include "auto/prelude.h"
#include "types_ghidra.h"

extern s32 * func_00179258();
extern s32 D_0040F4D4;
extern s128 * func_00178D30();
extern s32 func_0018A2C8();
extern s32 func_00181AD0();

void func_00189B28(void *arg0, void *arg1) {
    s32 *temp_4;

    temp_4 = func_00179258(D_0040F4D4 + 0xFA8, M2C_FIELD(arg1, s32 *, 0));
    M2C_FIELD(arg1, s8 *, 5) = 1;
    M2C_FIELD(arg1, s128 *, 0x20) = (s128) *func_00178D30(temp_4);
    M2C_FIELD(arg1, s128 *, 0x30) = (s128) M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x130), void **, 0x7C), s128 *, 0xA0);
}

s32 func_00189B90(s32 arg0, s32 arg1) {
    s32 temp_2;
    s32 temp_3;
    s32 var_5;

    var_5 = arg0;
    temp_3 = var_5 + 0x120;
loop_1:
    if (M2C_FIELD(var_5, s32 *, 0) != arg1) {
        var_5 += 0x60;
        temp_2 = var_5 < temp_3;
        if (temp_2 == 0) {
            return temp_2;
        }
        goto loop_1;
    }
    func_0018A2C8(arg0, var_5);
    return func_00181AD0(M2C_FIELD(arg0, s32 *, 0x130) + 0xEC0, 3);
}

s32 func_00189BF8(void *arg0, s32 arg1)
{
  void *new_var2;
  int new_var;
  new_var2 = arg0;
  new_var = (M2C_FIELD(new_var2, s32 *, 0x124)) & (1 << arg1);
  return new_var != 0;
  if (!arg1)
  {
  }
}
