#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00179060();
extern s32 func_0016FA50();

void func_0016E660(s32 arg0, void *arg1)
{
 do { M2C_FIELD(arg1, s32 *, 0x380) = func_00179060(arg0 + 0xFA8); func_0016FA50(arg0 + 0x22B28, arg1); } while (0);
}
