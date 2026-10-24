#include "ps2/prelude.h"

#include "types_ghidra.h"
extern s32 func_0036D518();
extern s32 func_0036E2F0();
extern s32 func_0036D568();

s32 func_0036E360(void) {
    s32 temp_16;
    s32 temp_17;

    temp_16 = func_0036D518();
    temp_17 = func_0036E2F0();
    if (temp_16 != 0) {
        func_0036D568();
    }
    return temp_17;
}
