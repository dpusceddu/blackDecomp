#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001DD3E0();
extern s32 func_001D9760();
extern void * D_0040F510;

s32 func_001EC560(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x1C);
    if (temp_4 != 0) {
        if (func_001DD3E0(temp_4) == 0) {
            return 0;
        }
        func_001D9760(M2C_FIELD(D_0040F510, s32 *, 0xCBDC), M2C_FIELD(arg0, s32 *, 0x1C));
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        /* Duplicate return node #4. Try simplifying control flow for better match */
        return 1;
    }
    return 1;
}

s32 func_001EC5C8(void *arg0)
{
  int new_var;
  s32 temp_3;
  s32 temp_3_2;
  void *new_var2;
  s32 var_5;
  void *temp_2;
  void *temp_4;
  temp_2 = *((void **) (((s8 *) arg0) + 0x20));
  var_5 = 0;
  new_var2 = temp_2;
  if (new_var2 != NULL)
  {
    new_var = 1;
    temp_3 = M2C_FIELD(temp_2, s32 *, 0x10);
    var_5 = (temp_3 >= new_var) ? (temp_3) : (0);
  }
  temp_4 = *((void **) (((s8 *) arg0) + 0x24));
  if (temp_4 != NULL)
  {
    temp_3_2 = M2C_FIELD(temp_4, s32 *, 0x10);
    var_5 = (var_5 < temp_3_2) ? (temp_3_2) : (var_5);
  }
  return var_5;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001EC600);
