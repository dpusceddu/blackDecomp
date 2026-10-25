#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001A24B8();
extern s32 func_00173690();
extern void func_00173658();

s32 func_001A3A08(void *arg0)
{
  func_001A24B8();
  func_00173690(arg0 + 0x78);
  M2C_FIELD(arg0, s32 *, 0x74) = 0;
  M2C_FIELD(arg0, s8 *, 0x88) = 7;
  func_00173658(arg0 + 0x84);
  return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A3A50);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A3CA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A3F20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A3F68);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A40D0);

s32 func_001A40D8(void) {
    return 1;
}

s32 func_001A40E0(s32 arg0) {
    s32 temp_16;
    s32 temp_17;

    temp_16 = arg0;
    func_001A24B8(arg0);
    temp_17 = temp_16 + 0x70;
    func_00173690(temp_17);
    M2C_FIELD(temp_17, f32 *, 4) = -1.0f;
    func_00173690(temp_16 + 0x78);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A4130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A4280);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A4428);

s32 func_001A44F8(s32 arg0) {
    s32 temp_16;
    s32 temp_17;

    temp_16 = arg0;
    func_001A24B8(arg0);
    temp_17 = temp_16 + 0x70;
    func_00173690(temp_17);
    M2C_FIELD(temp_17, f32 *, 4) = -1.0f;
    func_00173690(temp_16 + 0x78);
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A4548);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A4698);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_1a24b8_1a3a08", func_001A4860);
