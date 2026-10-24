/* Translation unit kynapse/tu_2da208 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"

extern s32 func_002E7610();
extern M2C_UNK D_00450EB8;
extern M2C_UNK func_002DA208;
extern M2C_UNK * D_00450FC8;
extern M2C_UNK D_003E5E40;
extern s32 func_002E74E0();

void func_002DA920(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002E7610(&D_00450EB8, "CPathWayManager", &func_002DA208, 0, 0, 0);
            return;
        }
        D_00450FC8 = &D_003E5E40;
    }
}

s32 func_002DA980(void *arg0, void *arg1)
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

/* Assembly between the functions: func_002DA9B0 (192 bytes), func_002DAA70 (152 bytes), func_002DAB08 (232 bytes), func_002DABF0 (96 bytes), func_002DAC50 (128 bytes) */

void func_002DACD0(void) {
    func_002DA920(1, 0xFFFF);
}

void func_002DACF0(void) {
    func_002DA920(0, 0xFFFF);
}
