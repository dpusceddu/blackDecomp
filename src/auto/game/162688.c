#include "auto/prelude.h"

extern s32 func_00160ED8();
extern s32 func_00177C90(s32, void *);

s32 func_00162688(void *arg0) {
    s32 temp_4;

    func_00160ED8();
    temp_4 = M2C_FIELD(arg0, s32 *, 0x90);
    if (temp_4 != 0) {
        func_00177C90(temp_4, arg0 + 0x20);
        M2C_FIELD(arg0, s32 *, 0x90) = 0;
    }
    return 1;
}
