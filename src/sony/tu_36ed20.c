#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00367CC0();
extern s32 func_0036ED70();
extern s32 func_00367CD0();

void func_0036ED20(void) {
    __asm__ volatile("li $3, 86\n\tsyscall");
}

void func_0036ED30(void) {
    if (func_00367CC0() == 0x02000000) {
        func_0036ED70();
        return;
    }
    func_00367CD0();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/sony/tu_36ed20", func_0036ED70);
