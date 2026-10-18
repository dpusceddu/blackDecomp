#include "auto/prelude.h"

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
