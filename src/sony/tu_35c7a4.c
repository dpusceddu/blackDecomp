#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00365F80();
extern void * D_003D6944;
extern s32 func_00365D48(s32 *arg0, s16 arg1);
extern void *D_003D6944;
extern s32 func_003605B8();
extern s32 func_00364DA8();
extern void func_0035EBB0(void *);
extern s32 func_00364AB8(void *, s32, s32);
extern void func_0035EC10(void *);
extern s32 func_003639A0(void *, s32);
extern s32 func_003640D0(void *, s32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035C7A4);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035C8D4);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035CA74);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035CBC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035CCD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035CE20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035CFD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D1A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D368);

s32 func_0035D378(s32 arg0) {
    return func_0035D3C8(arg0, (s32) func_00365F80);
}

void func_0035D398(void) {
    func_0035D378(D_003D6944);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D3C0);

s32 func_0035D3C8(s32 arg0, s32 arg1)
{
  s32 var_16;
  s32 var_19;
  void *var_17;
  void *var_18;
  var_18 = arg0 + 0x1D8;
  var_19 = 0;
  if (var_18 != NULL)
  {
    do
    {
      var_16 = M2C_FIELD(var_18, s32 *, 4);
      var_16 = var_16 - 1;
      var_17 = *((void **) (((s8 *) var_18) + 8));
      if (var_16 >= 0)
      {
        do
        {
          if ((M2C_FIELD(var_17, s16 *, 0xC)) != 0)
          {
            var_19 |= ((s32 (*)(void *)) arg1)(var_17);
          }
          var_16 -= 1;
          var_17 += 0x58;
        }
        while (var_16 >= 0);
      }
      var_18 = *((void **) (((s8 *) var_18) + 0));
    }
    while (var_18 != NULL);
  }
  return var_19;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D460);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D528);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D530);

void func_0035D598(void) {
    func_00365F80();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D5B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D720);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D728);

s32 func_0035D7A8(void) {
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D7B0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D848);

#include "ps2/recovered_types.h"
extern s64 func_00365E00(s32 *, s32, s32, s32);
extern s64 func_00365F20(s32 *, s32, void *, s32);

s32 func_0035D8B0(void *arg0, void *arg1, s32 arg2) {
    if (M2C_FIELD(arg0, u16 *, 0xC) & 0x100) {
        func_00365E00(M2C_FIELD(arg0, s32 **, 0x54), (s32) M2C_FIELD(arg0, s16 *, 0xE), 0, 2);
    }
    M2C_FIELD(arg0, u16 *, 0xC) = (u16) (M2C_FIELD(arg0, u16 *, 0xC) & 0xEFFF);
    return (s32) ((s64) (func_00365F20(M2C_FIELD(arg0, s32 **, 0x54), (s32) M2C_FIELD(arg0, s16 *, 0xE), arg1, arg2) << 0x20) >> 0x20);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D930);

void func_0035D998(void *arg0) {
    func_00365D48(M2C_FIELD(arg0, s32 **, 0x54), M2C_FIELD(arg0, s16 *, 0xE));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035D9B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035E4C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035E5B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035E610);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035E680);

s32 func_0035E690(s32 arg0)
{
  s32 temp_4;
  void *var_5;
  s8 *new_var;
  var_5 = *((void **) (((s8 *) D_003D6944) + 0x148));
  if (var_5 == NULL)
  {
    var_5 = D_003D6944 + 0x14C;
    *((void **) (((s8 *) D_003D6944) + 0x148)) = var_5;
  }
  if ((M2C_FIELD(var_5, s32 *, 4)) >= 0x20)
  {
    var_5 = func_0035E7D8(0x88U, var_5);
    if (var_5 != NULL)
    {
      M2C_FIELD(var_5, s32 *, 4) = 0;
      *((void **) (((s8 *) var_5) + 0)) = (void *) (*((void **) (((s8 *) D_003D6944) + 0x148)));
      *((void **) (((s8 *) D_003D6944) + 0x148)) = var_5;
      goto block_8;
    }
    return -1;
  }
  block_8:
  temp_4 = M2C_FIELD(var_5, s32 *, 4);

  new_var = ((s8 *) (var_5 + (temp_4 * 4))) + 8;
  *((s32 *) new_var) = arg0;
  M2C_FIELD(var_5, s32 *, 4) = (s32) (temp_4 + 1);
  return 0;
}

s32 func_0035E730(s32 arg0) {
    return func_003605B8(arg0, 0);
}

s32 func_0035E750(s32 arg0)
{
  return (s32) (((s64) ((func_00364DA8(arg0, 0, 0xA) & 0xFFFFFFFFFFFFFFFFu) << 0x20)) >> 0x20);
}

s32 func_0035E778(s32 arg0, s32 arg1) {
    s32 temp_17;

    func_0035EBB0(D_003D6944);
    temp_17 = func_00364AB8(D_003D6944, arg0, arg1);
    func_0035EC10(D_003D6944);
    return temp_17;
}

s32 func_0035E7D8(s32 arg0) {
    s32 temp_16;

    func_0035EBB0(D_003D6944);
    temp_16 = func_003639A0(D_003D6944, arg0);
    func_0035EC10(D_003D6944);
    return temp_16;
}

void func_0035E828(s32 arg0) {
    func_0035EBB0(D_003D6944);
    func_003640D0(D_003D6944, arg0);
    func_0035EC10(D_003D6944);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_35c7a4", func_0035E870);
