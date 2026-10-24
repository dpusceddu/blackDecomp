#include "include_asm.h"
#include "ps2/prelude.h"
#include "ps2/prototypes.h"

extern s32 D_00443630;
extern s32 func_0028FB08();
extern s32 func_0028FAB0();
extern s32 func_0035D398();
extern s32 func_00100218();

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028FAB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028FB08);

void func_0028FBB8(void) {
    if (D_00443630 == 0) {
        D_00443630 = 1;
        func_0028FB08();
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0028FBD8);

void func_002902C8(s32 arg0) {
    func_0028FAB0();
    func_0035D398();
    func_00100218(arg0);
}
