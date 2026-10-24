#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00368E20);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00368E58);

#define TYPES_GHIDRA_NO_PROTOTYPES
#include "types_ghidra.h"
#undef TYPES_GHIDRA_NO_PROTOTYPES
extern s32 func_00368E20(s32);

void func_00368F08(s32 arg0) {
    if (arg0 == 0xA) {
        func_00368E20(0xD);
        func_00368E20(0xA);
        return;
    }
    func_00368E20(arg0);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00368F40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00368FD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003691A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00369EC0);
