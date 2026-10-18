#include "auto/prelude.h"

extern void * D_0040F0E0;
extern s32 func_0026BBC0();
extern s32 func_001249F8();
extern s32 func_00103870();
extern void * D_0040F4BC;
extern s32 func_00103800();

void func_00121B40(void) {
    void *temp_16;

    temp_16 = M2C_FIELD(D_0040F0E0, void **, 0x21060);
    if (func_0026BBC0(M2C_FIELD(temp_16, s32 *, 0xC), func_001249F8(temp_16, 0x19)) & 0xFF) {
        if ((func_00103870(D_0040F0E0) == 0) && (M2C_FIELD(D_0040F4BC, u8 *, 0x1678) == 0)) {
            func_00103800(D_0040F0E0, 1);
        }
    }
}
