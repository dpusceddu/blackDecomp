#include "auto/prelude.h"

extern s32 func_0014D4F8();
extern s32 func_0014D4E0();
extern s32 func_0014D548();
extern s32 func_0014D5A8();
extern s32 func_0014D638(void *, f32);

void func_0014D420(void *arg0, f32 fparg0) {
    f32 temp_f0;
    void *temp_2;

    if (func_0014D4F8() == 0) {
        func_0014D4E0(arg0);
        return;
    }
    if (func_0014D548(arg0) == 0) {
        M2C_FIELD(arg0, s32 *, 4) = 0;
        func_0014D5A8(arg0);
    }
    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), void **, 0xB4);
    if ((M2C_FIELD(temp_2, u8 *, 0x3D) != 0) || (M2C_FIELD(temp_2, u8 *, 0x3E) != 0)) {
        M2C_FIELD(arg0, f32 *, 0x10) = 0.0f;
    }
    func_0014D638(arg0, fparg0);
    temp_f0 = M2C_FIELD(arg0, f32 *, 0x10) + fparg0;
    M2C_FIELD(arg0, f32 *, 0x10) = temp_f0;
    if (temp_f0 > 0.7f) {
        func_0014D4E0(arg0);
    }
}
