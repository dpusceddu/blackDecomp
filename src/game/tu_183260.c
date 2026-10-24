#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern void func_00181AD0(void *arg0, s32 arg1);
extern s32 func_00160E70();
extern s32 func_00165BC8(s32, s32);
extern s32 func_0018DDD8();
extern s32 func_00189BF8();
extern s32 func_00189250();
extern s32 func_00189AD0();
extern s32 func_0018C088();
extern s32 func_00181B08();
extern s32 func_00173610();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183260);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183380);

void func_001834B0(s32 *arg0) {
    func_00181AD0(*arg0 + 0xEC0, 0xD);
}

void func_001834D8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x30) = arg1;
}

s32 func_001834E0(void *arg0) {
    return M2C_FIELD(arg0, s32 *, 0x30);
}

s32 func_001834E8(void *arg0) {
    s32 var_2;

    var_2 = M2C_FIELD(arg0, s32 *, 4);
    if (var_2 < 0) {
        var_2 = M2C_FIELD(arg0, s32 *, 8);
    }
    return var_2;
}

s32 func_00183500(void *arg0)
{
  void *temp_2;
  temp_2 = *((void **) (((s8 *) arg0) + 0x30));
  if (temp_2 == NULL)
  {
    return 0;
  }
  if (arg0 || temp_2)
  {
    return *((s32 *) (((s8 *) temp_2) + (0x10 & 0xFFFFFFFFFFFFFFFFu)));
  }
  else
  {
    return M2C_FIELD(temp_2, s32 *, 0x10);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183520);

s128 func_00183558(void *arg0, void *arg1) {
    if (M2C_FIELD(arg1, s32 *, 0xC4) == 2) {
        return M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s128 *, 0x30);
    }
    return M2C_FIELD(arg1, s128 *, 0xA0);
}

void func_00183578(s32 arg0, s32 arg1) {
    func_00160E70();
    func_00165BC8(arg0, arg1);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001835B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183618);

s32 func_00183688(void *arg0, s64 arg1, void *arg2) {
    M2C_FIELD(arg0, s64 *, 0x10) = arg1;
    M2C_FIELD(arg0, void **, 0x18) = arg2;
    M2C_FIELD(arg0, s32 *, 8) = (s32) M2C_FIELD(arg2, u8 *, 0x24);
    M2C_FIELD(arg0, s32 *, 4) = (s32) M2C_FIELD(arg2, u8 *, 0x25);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001836A8);

s32 func_00183710(void *arg0, s8 arg1) {
    if ((arg1 >= 0) && (arg1 < M2C_FIELD(arg0, s32 *, 8))) {
        return M2C_FIELD(((arg1 * 4) + M2C_FIELD(arg0, s32 *, 0)), s32 *, 0);
    }
    return 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183748);

s8 func_00183858(void *arg0, s8 arg1) {
    s8 var_5;

    var_5 = arg1;
    if (var_5 < (M2C_FIELD(arg0, s32 *, 8) - 1)) {
        var_5 += 1;
    }
    return var_5;
}

s8 func_00183888(void *arg0, s8 arg1)
{
  s8 *new_var;
  new_var = ((s8 *) arg0) + 8;
  if (arg1 < ((*((s32 *) new_var)) - 1))
  {
    arg1 = arg1 + 1;
  }
  else
  {
    arg1 = 0;
  }
  return arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001838C0);

void func_00183910(s32 *arg0, s32 arg1) {
    *arg0 = arg1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183918);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183AA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183BC0);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern M2C_UNK D_003F6540;

s32 func_00183C80(s32 *arg0, s32 arg1, s32 arg2, f32 fparg0) {
    switch (arg1) {
    case 1:
    case 2:
    case 3:
    case 7:
    case 11:
        if (M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) != M2C_FIELD(arg2, s32 *, 0x3A4)) {
            return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
        }
        return 0;
    case 5:
        if ((M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, s32 *, 0), void **, 0x7C), s32 *, 0x3A4) != M2C_FIELD(arg2, s32 *, 0x3A4)) && (M2C_FIELD(arg0, s32 *, 0x64) >= 2)) {
            /* Duplicate return node #6. Try simplifying control flow for better match */
            return 0;
        }
        /* Duplicate return node #3. Try simplifying control flow for better match */
        return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
    default:
        return M2C_FIELD(((arg1 * 4) + ((s32) &D_003F6540)), s32 *, 0);
    }
}

void func_00183D28(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp[8] __attribute__((aligned(16)));
    void *temp_5;

    if (arg2 != 0) {
        temp_5 = M2C_FIELD(arg0, u32 *, 0);
        if ((M2C_FIELD(arg2, s32 *, 0x3A4) != M2C_FIELD(M2C_FIELD(temp_5, void **, 0x7C), s32 *, 0x3A4)) && ((M2C_FIELD(arg2, s32 *, 0xC4) == 2) || (func_0018DDD8((s32) (temp_5 + 0xC94)) != 0)) && (arg1 > 0) && (arg1 < 4) && (func_00189BF8((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), M2C_FIELD(arg2, s32 *, 0x380)) != 0) && (func_00189250((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), M2C_FIELD(arg2, s32 *, 0x380)) != 0)) {
            func_00189AD0((s32) (M2C_FIELD(arg0, u32 *, 0) + 0x150), arg2);
            func_0018C088((s32) sp, arg2);
            func_00181B08((s32) (M2C_FIELD(arg0, u32 *, 0) + 0xEC0), (s32) sp);
        }
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183E00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183EA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183EA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183EF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00183FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001840C8);

void * func_00184238(void *arg0, void *arg1) {
    return (void *) ((func_00173610(arg0 + (((s32) arg1 * 4) + 0x34)) ^ 1) & 0xFF);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00184268);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001842C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001843C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00184550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001847B8);
