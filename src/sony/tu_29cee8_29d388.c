#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_0029D228();

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
