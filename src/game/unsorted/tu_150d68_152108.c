#include "include_asm.h"
#include "ps2/prelude.h"

extern void * func_001AFD80();
extern s32 func_001B6CF8();
extern s32 D_0040F4D8;
extern s32 func_001B37C8();

u8 func_00152108(void *arg0) {
    void *temp_2;
    void *temp_2_2;

    temp_2_2 = func_001AFD80(arg0 + 0x1A0, M2C_FIELD(arg0, s32 *, 0x118));
    if (temp_2_2 == NULL) {
        return 0U;
    }
    temp_2 = M2C_FIELD(temp_2_2, void **, 0xC0);
    if (temp_2 == NULL) {
        return 0U;
    }
    return M2C_FIELD(*M2C_FIELD(temp_2, void ***, 0x24), u8 *, 4);
}

void func_00152148(void *arg0)
{
  u16 temp_3;
  func_001B6CF8(D_0040F4D8 + 0x66290, arg0, 1);
  ;
  if ((M2C_FIELD(arg0, u16 *, 0x1BC)) != 0xFFFF)
  {
    func_001B37C8(D_0040F4D8 + 0x33C40, M2C_FIELD(arg0, u16 *, 0x1BC));
  }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68_152108", func_001521B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_150d68_152108", func_00152588);
