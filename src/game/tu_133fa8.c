#include "include_asm.h"
#include "ps2/prelude.h"
#include "types_ghidra.h"

extern s32 func_00126098();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00133FA8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001347B8);

void func_00134970(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_00126098(arg0, arg1, arg2, arg3, arg4, arg5, arg0 + 0x1E0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00134990);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00134BB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00134C98);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00134FD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00135138);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001353F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001354E0);

void * func_00135550(void *arg0) {
    return M2C_FIELD(arg0, void **, 0x32C);
}
