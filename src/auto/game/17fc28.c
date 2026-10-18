#include "auto/prelude.h"

extern s32 func_00181AD0(void *, M2C_UNK);

void func_0017FC28(void) {

}

void func_0017FC30(void *arg0, s32 arg1) {
    void *temp_4;

    if (arg1 == 2) {
        temp_4 = M2C_FIELD(arg0, void **, 0x44);
        if (M2C_FIELD(temp_4, s32 *, 0x80) == 1) {
            func_00181AD0(temp_4 + 0xEC0, 4);
        }
    }
}
