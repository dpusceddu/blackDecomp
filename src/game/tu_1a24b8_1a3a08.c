/* Translation unit tu_1a24b8 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "ps2/prelude.h"
#include "types_ghidra.h"

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

/* Assembly between the functions: func_001A3A50 (600 bytes), func_001A3CA8 (632 bytes), func_001A3F20 (72 bytes), func_001A3F68 (360 bytes), func_001A40D0 (8 bytes) */

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

/* Assembly between the functions: func_001A4130 (336 bytes), func_001A4280 (424 bytes), func_001A4428 (208 bytes) */

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
