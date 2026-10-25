#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_00274F80();
extern s32 func_0028F618(s32);
extern s32 func_0028F718(s32);
extern s32 func_0028FA60(s32);

void func_00271650(void *arg0)
{
  void *new_var;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  new_var = arg0;
  if (new_var && new_var)
  {
  }
  M2C_FIELD(new_var, s32 *, 4) = -1;
  M2C_FIELD(new_var, s32 *, 8) = -1;
}

void * func_00271668(void *arg0, void *arg1, void *arg2, void *arg3, void *arg4) {
    s32 temp_3;
    s32 temp_7;

    temp_7 = (s32) (((s32) arg2 > -1) ? arg2 : (arg2 + 3)) >> 2;
    temp_3 = (s32) (((s32) arg3 > -1) ? arg3 : (arg3 + 3)) >> 2;
    M2C_FIELD(arg0, void **, 0x14) = arg4;
    M2C_FIELD(arg0, void **, 0xC) = arg2;
    M2C_FIELD(arg0, void **, 0x10) = arg3;
    M2C_FIELD(arg0, s32 *, 4) = temp_7;
    M2C_FIELD(arg0, s32 *, 8) = temp_3;
    if (arg2 != (temp_7 * 4)) {
        M2C_FIELD(arg0, s32 *, 4) = (s32) (temp_7 + 1);
    }
    if (arg3 != (temp_3 * 4)) {
        M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg0, s32 *, 8) + 1);
    }
    M2C_FIELD(arg0, void **, 0) = func_00274F80(arg1, (void *) (((s32) M2C_FIELD(arg0, void **, 0xC) * (s32) M2C_FIELD(arg0, void **, 0x10)) << 0xA));
    return (void *)1;
}

void func_00271710(void *arg0)
{
  void *new_var;
  M2C_FIELD(arg0, s32 *, 0) = 0;
  new_var = arg0;
  if (new_var && new_var)
  {
  }
  M2C_FIELD(new_var, s32 *, 4) = -1;
  M2C_FIELD(new_var, s32 *, 8) = -1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650", func_00271728);

s32 func_00271968(s32 arg0, s32 arg1, s32 arg2) {
    func_0028F618(arg2 + 0xB8);
    return 1;
}

s32 func_00271988(s32 arg0, s32 arg1, s32 arg2) {
    func_0028F718(arg2 + 0xB8);
    return 1;
}

s32 func_002719A8(s32 arg0) {
    return func_0028FA60(arg0 + 0xB8) <= 0xFFFF;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650", func_002719D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650", func_00271AF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_271650", func_00271B50);
