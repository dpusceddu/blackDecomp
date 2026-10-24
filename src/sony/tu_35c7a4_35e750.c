#include "ps2/prelude.h"

extern s32 func_00364DA8();

s32 func_0035E750(s32 arg0)
{
  return (s32) (((s64) ((func_00364DA8(arg0, 0, 0xA) & 0xFFFFFFFFFFFFFFFFu) << 0x20)) >> 0x20);
}
