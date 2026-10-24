#include "include_asm.h"
#include "ps2/prelude.h"

extern void *D_0040F4D0;
extern s32 D_003BCEE8;
extern unsigned char func_00107D20();

s32 func_0016B788(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x48) = 0x37;
    return 1;
}

void func_0016B798(void) {

}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016B7A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BA18);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BBF8);

void func_0016BE08(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0x48) = arg1;
}

void func_0016BE10(void)
{
  s32 temp_2;
  temp_2 = M2C_FIELD(D_0040F4D0, s32 *, 0x8F4);
  if (temp_2 > 0)
  {
    D_003BCEE8 = (((((((((func_00107D20(temp_2 * 0xC) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF) & 0xFF;
    return;
  }
  D_003BCEE8 = 0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BE60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BEA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016BEE0);
