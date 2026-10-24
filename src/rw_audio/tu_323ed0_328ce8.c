#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern void func_003299E8();
extern M2C_UNK D_0045C120;

s32 func_00328CE8(s32 arg0, u32 arg1) {
    func_003299E8(&D_0045C120, arg0, arg1, 1);
    return 1;
}

void func_00328D18(s32 arg0, s32 arg1)
{
  s32 new_var;
  new_var = arg1;
  func_003299E8(&D_0045C120, arg0, (long) new_var, 0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00328D48);
