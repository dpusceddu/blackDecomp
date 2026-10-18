#include "auto/prelude.h"

extern s32 func_0013EE30();

void func_0013F2C8(void) {
    func_0013EE30();
}

void func_0013F2E8(void *arg0) {
    void *temp_2;

    M2C_FIELD(arg0, s32 *, 0x90) = 0;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    temp_2 = M2C_FIELD(arg0, void **, 0x7C);
    M2C_FIELD(arg0, f32 *, 8) = (f32) M2C_FIELD(temp_2, f32 *, 0x4F8);
    M2C_FIELD(arg0, f32 *, 0xC) = (f32) M2C_FIELD(temp_2, f32 *, 0x4FC);
}

void func_0013F308(void) {

}
