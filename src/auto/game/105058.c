#include "auto/prelude.h"

extern void func_00109E70(s32);
extern void func_0010A860(void *arg0);
extern s32 func_00102080();

void func_00105058(void *arg0) {
    void *temp_4;

    func_00109E70(arg0 + 0x4C);
    func_0010A860(arg0 + 0x218);
    temp_4 = M2C_FIELD(arg0, void **, 0xD50);
    if (temp_4 != NULL) {
        func_00102080(temp_4);
        M2C_FIELD(arg0, void **, 0xD50) = NULL;
    }
    M2C_FIELD(arg0, s32 *, 0) = 0x39;
}
