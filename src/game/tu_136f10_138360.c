#include "auto/prelude.h"

const u32 rodata_003F5168[12] __asm__("D_003F5168") __attribute__((aligned(8))) = { 0x3DCCCCCD, 0x3E800000, 0x3E19999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D99999A, 0x3D851EB8, 0x3D99999A, 0x3D851EB8, 0x00000000 };
#include "types_ghidra.h"
extern volatile char D_003F5168;

f32 func_00138360(s32 arg0)
{
  return *((f32 *) (((s8 *) ((arg0 * 4) + (&D_003F5168))) + 0));
}
