/* Translation unit kynapse/tu_2dca40 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_004510F0;
extern M2C_UNK func_002DCA40;
extern M2C_UNK * D_00451200;
extern M2C_UNK D_003E5E40;
extern s32 func_002E74E0();

void func_002DD158(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_004510F0, "CScriptManager", &func_002DCA40, 0, 0, 0);
            return;
        }
        D_00451200 = &D_003E5E40;
    }
}

s32 func_002DD1B8(void *arg0, void *arg1)
{
  void *new_var;
  if ((float) (arg1 != NULL))
  {
    new_var = arg1;
    if ((new_var && new_var) && new_var)
    {
    }
    return func_002E74E0(arg0, new_var) != 0;
  }
  if (new_var || arg0)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}

/* Assembly between the functions: func_002DD1E8 (192 bytes), func_002DD2A8 (152 bytes), func_002DD340 (232 bytes), func_002DD428 (96 bytes), func_002DD488 (128 bytes) */

void func_002DD508(void) {
    func_002DD158(1, 0xFFFF);
}

void func_002DD528(void) {
    func_002DD158(0, 0xFFFF);
}
