#include "include_asm.h"
#include "ps2/prelude.h"

s32 func_0029D108(s32 arg0) {
    u32 temp_4;

    temp_4 = arg0 & 0xFF;
    return (((temp_4 / 10U) * 6) + temp_4) & 0xFF;
}

s32 func_0029D138(s32 arg0)
{
  u32 temp_2;
  temp_2 = arg0 & 0xFF;
  return (temp_2 - (((((((((temp_2 >> 4) * 6) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu) & 0xFFu)) & 0xFF;
}
