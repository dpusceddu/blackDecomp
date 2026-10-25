#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001AFDE0();
extern s32 func_001AFE38();
extern s32 func_001C6F10(s32, u64, M2C_UNK, M2C_UNK);
extern void * D_0040F4C0;
extern s32 func_001C5F48(void *);
extern s32 func_00271230(M2C_UNK *, M2C_UNK, M2C_UNK);
extern M2C_UNK D_00440280;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C5F48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C6010);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C62A0);

s32 func_001C62A8(s32 arg0)
{
  int new_var;
  s32 temp_2;
  s32 temp_2_2;
  temp_2 = M2C_FIELD(arg0, s32 *, 0x20);
  if (temp_2 != 0)
  {
    M2C_FIELD(arg0, s32 *, 0x20) = (s32) (temp_2 + arg0);
  }
  temp_2_2 = M2C_FIELD(arg0, s32 *, 0x24);
  new_var = 0xFF;
  if (temp_2_2 != 0)
  {
    M2C_FIELD(arg0, s32 *, 0x24) = (s32) (temp_2_2 + arg0);
  }
  M2C_FIELD(arg0, s8 *, 0x28) = new_var;
  new_var = new_var;
  return new_var;
}

s32 func_001C62D8(s32 *arg0, s32 arg1) {
    return *arg0 + (arg1 * 0x30);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C62F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C64E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C64E8);

void func_001C65E8(void) {
    func_001AFDE0();
}

s32 func_001C6608(s32 arg0) {
    func_001AFE38();
    func_001C6F10(arg0 + 0x70, (u64) ((s64) ((u32) M2C_FIELD(D_0040F4C0, u32 *, 0xD5E0) >> 0xB) << 0x20) >> 0x20, 0, 0xC);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C6660);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001C6668);

void func_001C6A68(void) {
    func_001C5F48(D_0040F4C0);
    func_00271230(&D_00440280, 0, 0);
}
