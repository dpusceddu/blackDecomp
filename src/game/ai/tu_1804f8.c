#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 func_001806D0();
extern s32 func_001808D0();
extern s32 func_001808D8();
extern void func_001809C8();
extern s32 func_00180CD8();
extern s32 func_00173640(void *, f32);

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001804F8);

void func_00180610(void *arg0) {
    func_001806D0();
    func_001808D0(arg0);
    func_001808D8(arg0);
    func_001809C8(arg0);
    if ((M2C_FIELD(arg0, u8 *, 0x14C) != 0) && (func_00180CD8(arg0) == 0)) {
        func_00173640(arg0 + 0x148, 1.0f);
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00180678);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001806D0);
