/* Translation unit tu_136f10 of the TU map: its source functions in address order; assembly functions between them stay
   in the image and are placed by address. */
#include "auto/prelude.h"
#include "types_ghidra.h"

extern M2C_UNK D_003F5138;
const u32 rodata_003F5168[12] __asm__("D_003F5168") __attribute__((aligned(8))) = { 0x3DCCCCCD, 0x3E800000, 0x3E19999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D851EB8, 0x3D99999A, 0x3D851EB8, 0x00000000 };
extern volatile char D_003F5168;

f32 func_00138348(s32 arg0) {
    return M2C_FIELD(((arg0 * 4) + ((s32) &D_003F5138)), f32 *, 0);
}

f32 func_00138360(s32 arg0)
{
  return *((f32 *) (((s8 *) ((arg0 * 4) + (&D_003F5168))) + 0));
}
