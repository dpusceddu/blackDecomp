#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001D74C8(s32);
extern void * D_0040F510;
extern s32 func_001435D0();
extern void func_00144038();
extern s32 D_003BCEAC;
extern s32 func_00143908();

s32 func_001435F8(void *arg0, s32 arg1, s32 arg2) {
    M2C_FIELD(arg0, s32 *, 8) = arg1;
    M2C_FIELD(arg0, s32 *, 0xC) = arg2;
    M2C_FIELD(arg0, s32 *, 0x10) = func_001D74C8(M2C_FIELD(M2C_FIELD(D_0040F510, void **, 0xCBD8), s32 *, 0xC));
    M2C_FIELD(arg0, s8 *, 0x31) = 0;
    return 1;
}

s32 func_00143648(s32 arg0, s32 arg1) {
    s32 temp_6;
    s32 var_4;
    void *temp_2;
    void *var_3;

    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 4), void **, 0x20);
    temp_6 = M2C_FIELD(temp_2, s32 *, 8);
    var_4 = 0;
    if (temp_6 <= 0) {
        goto block_5;
    }
    var_3 = M2C_FIELD(temp_2, void **, 0xC);
loop_2:
    var_4 += 1;
    if (M2C_FIELD(var_3, s64 *, 0) != arg1) {
        goto block_4;
    }
    return M2C_FIELD(var_3, s32 *, 8);
block_4:
    var_3 += 0x10;
    if (var_4 < temp_6) {
        goto loop_2;
    }
block_5:
    return 0;
}

void func_00143688(void *arg0)
{
  s32 temp_17;
  s32 temp_18;
  temp_17 = arg0 + 8;
  func_001435D0(temp_17, 0xD);
  temp_18 = arg0 + 0x40;
  func_001435D0(temp_18, 0xE);
  M2C_FIELD(arg0, s32 *, 0x80) = temp_17;
  M2C_FIELD(arg0, s32 *, 0x7C) = temp_18;
  M2C_FIELD(arg0, s8 *, 0xC4) = 0;
  func_00144038(arg0, D_003BCEAC);
  M2C_FIELD(arg0, s8 *, 0) = 0;
  M2C_FIELD(arg0, s32 *, 0xC8) = 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00143700);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001437D8);

s32 func_001438A8(void) {
    return func_00143908() != 0;
}

s32 func_001438C8(s32 arg0) {
    return func_00143908(arg0, 0) != 0;
}

s32 func_001438E8(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x80);
    if (M2C_FIELD(temp_4, s32 *, 0x1C) == 9) {
        M2C_FIELD(temp_4, s32 *, 0x1C) = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00143908);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00143B00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00143C80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00143D90);

#include "ps2/recovered_types.h"
extern s32 func_001093C0(s32, void *, s32, s32, s32, void *, s32, s32);
extern s32 D_0040F4C4;

void func_00143F90(void *arg0, void *arg1, s32 arg2, void *arg3, s32 arg4) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x80);
    if (M2C_FIELD(temp_4, s32 *, 0x1C) == 9) {
        func_001093C0(D_0040F4C4, arg1, 6, M2C_FIELD(temp_4, s32 *, 0), arg2, arg3, arg4, 0x02000000);
    }
}
