#include "include_asm.h"
#include "ps2/prelude.h"

extern char D_00407EB8[];
const char rodata_00407EB8[32] __asm__("D_00407EB8") __attribute__((aligned(8))) = "CAstarData" "\000\000\000\000\000\000" "Q24Kaim7CObject" "\000";
extern s32 func_002F35B0();
extern M2C_UNK D_00454788;
extern M2C_UNK func_002FD998;
extern M2C_UNK * D_00454898;
extern M2C_UNK D_003EC200;
extern M2C_UNK D_003EF7B0;

void func_002FEA88(s32 arg0, s32 arg1) {
    if (arg1 == 0xFFFF) {
        if (arg0 != 0) {
            func_002F35B0(&D_00454788, D_00407EB8, &func_002FD998);
            return;
        }
        D_00454898 = &D_003EC200;
    }
}

void *func_002FEAE0(void *arg0, void *arg1)
{
  *((void **) (((s8 *) arg0) + 4)) = arg1;
  *((M2C_UNK **) (((s8 *) arg0) + 0)) = &D_003EF7B0;
  M2C_FIELD(arg0, s32 *, 8) = (s32) (M2C_FIELD(arg1, s32 *, 0x14));
  M2C_FIELD(arg0, s32 *, 0xC) = 0;
  if (arg0)
  {
  }
  M2C_FIELD(arg0, s32 *, 0x10) = 0;
  return arg0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002FEB08);

void func_002FEBD0(void) {
    func_002FEA88(1, 0xFFFF);
}

void func_002FEBF0(void) {
    func_002FEA88(0, 0xFFFF);
}
