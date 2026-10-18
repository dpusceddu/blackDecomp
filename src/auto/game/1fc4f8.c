#include "auto/prelude.h"

extern s32 func_0035D728(void *, M2C_UNK *, s32);
extern M2C_UNK D_003F9598;
extern s32 func_00275260(void *, s32, M2C_UNK);

void func_001FC4F8(void) {

}

void func_001FC500(void) {

}

void func_001FC508(s32 arg0, s32 arg1) {
    void *temp_16;

    temp_16 = arg0 + 0x16C;
    func_0035D728(temp_16, &D_003F9598, arg1 & 0xFFFF);
    func_00275260(temp_16, arg0 + 0x17C, 4);
}
