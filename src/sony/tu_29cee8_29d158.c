#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern u8 func_0029D138();
extern u8 func_0029D108();
extern s32 func_0029D228();

void func_0029D158(void *arg0) {
    M2C_FIELD(arg0, u8 *, 7) = func_0029D138(M2C_FIELD(arg0, u8 *, 7));
    M2C_FIELD(arg0, u8 *, 6) = func_0029D138(M2C_FIELD(arg0, u8 *, 6));
    M2C_FIELD(arg0, u8 *, 5) = func_0029D138(M2C_FIELD(arg0, u8 *, 5));
    M2C_FIELD(arg0, u8 *, 3) = func_0029D138(M2C_FIELD(arg0, u8 *, 3));
    M2C_FIELD(arg0, u8 *, 2) = func_0029D138(M2C_FIELD(arg0, u8 *, 2));
    M2C_FIELD(arg0, u8 *, 1) = func_0029D138(M2C_FIELD(arg0, u8 *, 1));
}

void func_0029D1C0(void *arg0) {
    M2C_FIELD(arg0, u8 *, 7) = func_0029D108(M2C_FIELD(arg0, u8 *, 7));
    M2C_FIELD(arg0, u8 *, 6) = func_0029D108(M2C_FIELD(arg0, u8 *, 6));
    M2C_FIELD(arg0, u8 *, 5) = func_0029D108(M2C_FIELD(arg0, u8 *, 5));
    M2C_FIELD(arg0, u8 *, 3) = func_0029D108(M2C_FIELD(arg0, u8 *, 3));
    M2C_FIELD(arg0, u8 *, 2) = func_0029D108(M2C_FIELD(arg0, u8 *, 2));
    M2C_FIELD(arg0, u8 *, 1) = func_0029D108(M2C_FIELD(arg0, u8 *, 1));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D228);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D2E0);

short func_0029D388(void *arg0)
{
  unsigned int temp_3;
  temp_3 = M2C_FIELD(arg0, u8 *, 3);
  temp_3 = temp_3 + 1;
  M2C_FIELD(arg0, u8 *, 3) = temp_3;
  if ((temp_3 & 0xFF) == 0x18)
  {
    M2C_FIELD(arg0, u8 *, 3) = 0U;
    func_0029D228(arg0, arg0);
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D3B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D3E0);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_0029D3E0(void *, s32);

void func_0029D470(void *arg0) {
    func_0029D3E0(arg0, -0x21C);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0029D478);
