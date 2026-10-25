#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_001C9110();
extern s32 func_001CA0F0(void *);
extern s32 func_00108328();
extern s32 D_0040F4C4;

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001C88C8);

s32 func_001C8C28(void) {
    return 1;
}

void func_001C8C30(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001C8C38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001C8D20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001C8E30);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001C8ED8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001C8F08);

void func_001C9088(void *arg0) {
    if ((M2C_FIELD(arg0, s32 *, 0x40) != 0) && (M2C_FIELD(arg0, u8 *, 0x178) != 0)) {
        func_001C9110();
        func_001CA0F0(arg0);
        func_001CA200(arg0);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001C90D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001C9110);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001CA0F0);

void func_001CA200(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001CA208);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001CA258);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001CA290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001CA3B0);

void func_001CA578(s32 arg0, s32 arg1)
{
  s32 temp_2;
  int new_var;
  s8 *new_var2;
  s32 temp_2_2;
  temp_2_2 = M2C_FIELD(arg1, s32 *, 4);
  new_var = temp_2_2 != 0;
  new_var2 = ((s8 *) arg1) + 4;
  temp_2 = temp_2_2 + arg1;
  if (new_var)
  {
    *((s32 *) new_var2) = temp_2_2 + arg1;
  }
  return temp_2_2 + arg1;
}

void func_001CA590(s32 arg0, void *arg1, s32 arg2)
{
  s32 temp_2;
  s32 *new_var;
  s32 *new_var2;
  new_var = &(M2C_FIELD(arg1, s32 *, 4));
  temp_2 = *new_var;
  if (temp_2 != 0)
  {
    new_var2 = &(*((s32 *) (((s8 *) (((temp_2 - 1) * 4) + arg2)) + 0)));
    M2C_FIELD(arg1, s32 *, 4) = func_00108328(D_0040F4C4, *new_var2);
  }
}

void func_001CA5D8(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001CA5E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1c88c8", func_001CA7E0);
