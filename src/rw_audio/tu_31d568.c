#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_003165C8();
extern s32 func_00316618();
extern s32 func_00317E40();
extern s32 func_003186F0();
extern s32 func_00317A78();
extern s32 func_00318880();
extern s32 func_00312C48();
extern s32 func_003111A8();
extern s32 func_00317C20();
extern s32 func_00318950();
extern s32 func_00312C70();
extern void *func_0031E4C0();
extern s32 func_00316668();
extern M2C_UNK *D_00458768;
extern M2C_UNK *D_00458740;
extern M2C_UNK *D_00458718;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031D568);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031D6A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031D7A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031D988);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031DB28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031DC30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031DC40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031DDD8);

s32 func_0031DE30(s32 arg0, s32 arg1, s32 arg2) {
    func_003165C8(arg0, arg2);
    func_00316618(arg0, arg1);
    return arg0;
}

void *func_0031DE78(void *arg0)
{
  M2C_UNK (*temp_2)(M2C_UNK);
  unsigned short new_var;
  temp_2 = *((M2C_UNK (**)(M2C_UNK)) (0x3C + ((s8 *) arg0)));
  new_var = 0;
  if (temp_2 == ((void *) new_var))
  {
    if (temp_2)
    {
      return (void *) new_var;
    }
    else
    {
      return (void *) new_var;
    }
  }
  temp_2(new_var);
  return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031DEB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031DF28);

#include "ps2/recovered_types.h"
extern void * func_0031E0E0(s32, void *, s32, void *, s32);
extern s32 func_0031E5C8(s32, s32 *, void *);

s32 func_0031DF58(s32 arg0, void *arg1, void *arg2) {
    u8 sp[8] __attribute__((aligned(16)));

    *(void * *)(sp + 0) = arg1;
    *(void * *)(sp + 4) = arg2;
    func_0031E0E0(arg0, NULL, (s32) func_0031E5C8, sp, 1);
    return *(void * *)(sp + 4) != NULL;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031DF98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031DFB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031E000);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031E070);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031E0E0);

s32 func_0031E1F8(s32 arg0, s32 arg1, s32 arg2) {
    if (M2C_FIELD(arg0, s32 *, 0x48) != 0) {
        return 0;
    }
    if ((u16) M2C_FIELD(arg0, u16 *, 0x46) >= 2U) {
        if (arg2 != 0) {
            M2C_FIELD(arg0, s32 *, 0x48) = func_00317E40(arg1, (s32) M2C_FIELD(arg0, u16 *, 0x46), 1 << ((u32) M2C_FIELD(arg0, u32 *, 0x40) >> 0x1C), 1, 0, 0x3080A);
            M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) | 0x40);
        } else {
            M2C_FIELD(arg0, s32 *, 0x48) = func_003186F0(arg1, (s32) M2C_FIELD(arg0, u16 *, 0x46), 1 << ((u32) M2C_FIELD(arg0, u32 *, 0x40) >> 0x1C), 1, 0);
            M2C_FIELD(arg0, s32 *, 0xC) = (s32) (M2C_FIELD(arg0, s32 *, 0xC) | 0x80);
        }
    } else {
        M2C_FIELD(arg0, s32 *, 0x48) = 1;
    }
    return (M2C_FIELD(arg0, s32 *, 0x48) != 0) ? arg0 : 0;
}

s32 func_0031E2C0(s32 arg0, s32 arg1) {
    s32 temp_3;

    temp_3 = M2C_FIELD(arg0, s32 *, 0xC);
    if (temp_3 & 0x40) {
        return func_00317A78(M2C_FIELD(arg0, s32 *, 0x48), M2C_FIELD(arg0, s32 *, 0x58));
    }
    if (temp_3 & 0x80) {
        return func_00318880(M2C_FIELD(arg0, s32 *, 0x48), arg1);
    }
    return func_00312C48(arg1, M2C_FIELD(arg0, s32 *, 0x58));
}

s32 func_0031E320(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[16] __attribute__((aligned(16)));
    s32 temp_17;
    s32 temp_3;
    s32 temp_4;
    s32 temp_5;
    s32 var_16;
    s32 var_2;

    var_16 = arg0;
    temp_5 = M2C_FIELD(var_16, s32 *, 0x1C);
    var_2 = temp_5 & 8;
    temp_17 = M2C_FIELD(var_16, s32 *, 0);
    if (var_2 != 0) {
        var_16 = M2C_FIELD(var_16, s32 *, -4);
    } else {
        var_2 = temp_5 & 0x10;
        if (var_2 != 0) {
            var_2 = var_16 + func_003111A8(temp_17, temp_5 & 7, (s32) sp);
            var_16 = M2C_FIELD(var_2, s32 *, 0);
        }
    }
    temp_3 = M2C_FIELD(temp_17, s32 *, 0x48);
    if ((temp_3 != 0) && ((arg1 == 0) || (var_2 = M2C_FIELD(arg0, s32 *, 0x1C) & 0x20, (var_2 == 0)))) {
        temp_4 = M2C_FIELD(temp_17, s32 *, 0xC);
        if (temp_4 & 0x40) {
            return func_00317C20(temp_3, var_16);
        }
        if (temp_4 & 0x80) {
            return func_00318950(temp_3, var_16);
        }
        return func_00312C70(var_16);
    }
    if (arg1 != 0) {
        var_2 = ((s32 (*)(s32, s32)) arg1)(var_16, arg2);
    }
    return var_2;
}

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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31d568", func_0031E4C0);
