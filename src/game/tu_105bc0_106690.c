#include "ps2/prelude.h"

void func_00106690(void) {

}

void func_00106698(void *arg0) {
    void *temp_5;

    temp_5 = M2C_FIELD(arg0, void **, 0x30);
    if ((M2C_FIELD(temp_5, s32 *, 4) == 1) && (M2C_FIELD(arg0, u8 *, 0x24) == 0)) {
        M2C_FIELD(arg0, f32 *, 0x2C) = (f32) (M2C_FIELD(arg0, f32 *, 0x2C) - M2C_FIELD(temp_5, f32 *, 0x4C));
    }
}
