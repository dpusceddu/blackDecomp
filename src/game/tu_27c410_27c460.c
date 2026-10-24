/* Translation unit tu_27c410 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_0027C410();
extern s32 D_003C0DFC;

s32 func_0027C460(s32 arg0, s32 arg1) {
    return M2C_FIELD(func_0027C410(), s32 *, 0x10C) + (arg1 * 0x70);
}

/* Assembly between the functions: func_0027C498 (728 bytes), func_0027C770 (8 bytes), func_0027C778 (232 bytes) */

s8 *func_0027C860(s8 *arg0)
{
  s8 *var_5;
  u32 var_6;
  var_5 = arg0;
  var_6 = 0;
 do { } while (0);
  if ((*var_5) == 0x3A)
  {
    var_5 += 1;
  }
  else
  {
    loop_3:
    var_6 += 1;

    if (var_6 < 4U)
    {
 do { } while (0);
      if (!((*(var_5 + var_6)) == 0x3A))
      {
        goto loop_3;
      }
      else
      {
        var_5 += var_6 + 1;
      }
    }
  }
  return var_5;
}

/* Assembly between the functions: func_0027C8B0 (224 bytes) */

void func_0027C990(s32 arg0) {
    D_003C0DFC = arg0;
}

/* Assembly between the functions: func_0027C9A0 (280 bytes), func_0027CAB8 (264 bytes), func_0027CBC0 (40 bytes), func_0027CBE8 (144 bytes), func_0027CC78 (48 bytes), func_0027CCA8 (80 bytes), func_0027CCF8 (80 bytes) */

s32 func_0027CD48(void *arg0) {
    void *temp_3;

    temp_3 = M2C_FIELD(arg0, void **, 0x60);
    return M2C_FIELD(temp_3, s64 *, 0x10) >= M2C_FIELD(temp_3, s64 *, 8);
}
