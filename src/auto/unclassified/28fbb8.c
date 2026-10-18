#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 D_00443630;
extern s32 func_0028FB08();

void func_0028FBB8(void) {
    if (D_00443630 == 0) {
        D_00443630 = 1;
        func_0028FB08();
    }
}
