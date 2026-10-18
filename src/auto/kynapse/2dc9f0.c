#include "auto/prelude.h"

extern s32 D_003E6428;
extern s32 func_002DC7E0();

void func_002DC9F0(void) {
    D_003E6428 = 0;
}

void func_002DCA00(void) {
    func_002DC7E0(1, 0xFFFF);
}

void func_002DCA20(void) {
    func_002DC7E0(0, 0xFFFF);
}
