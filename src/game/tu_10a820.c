#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00278EA0(void *);

void func_0010A820(u8 *arg0) {
    if (*arg0 != 0) {
        func_00278EA0(arg0 + 0x20);
    }
}
