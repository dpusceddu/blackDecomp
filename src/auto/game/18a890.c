#include "auto/prelude.h"

extern s32 func_00188F10();
extern s32 func_00189740(s32, void *, M2C_UNK);
extern void * D_0040F4D0;

void func_0018A890(s32 arg0) {
    if (func_00188F10() == 0) {
        func_00189740(arg0, D_0040F4D0 + 0x30, 1);
    }
}
