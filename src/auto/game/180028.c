#include "auto/prelude.h"

#include "types_ghidra.h"
extern s32 func_00181F48(void *arg0, s32 arg1, s32 arg2, f32 fparg0, f32 fparg1);

void func_00180028(void *arg0) {
    void *temp_4;

    temp_4 = M2C_FIELD(arg0, void **, 0x44);
    if (M2C_FIELD(temp_4, s32 *, 0x80) == 1) {
        func_00181F48(temp_4 + 0xC80, 0, 0x13, 0.0f, 1.0f);
    }
}
