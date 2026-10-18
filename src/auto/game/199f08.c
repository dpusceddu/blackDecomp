#include "auto/prelude.h"

extern s32 func_00177C90(s32, s32);
extern s32 func_0017B358(s32);

void func_00199F08(void *arg0) {
    s32 temp_4;

    temp_4 = M2C_FIELD(arg0, s32 *, 0x38);
    if (temp_4 != 0) {
        func_00177C90(temp_4, M2C_FIELD(arg0, s32 *, 0) + 0x1F00);
        M2C_FIELD(arg0, s32 *, 0x38) = 0;
    }
}

void func_00199F48(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x38) = 0;
    func_0017B358(M2C_FIELD(arg0, s32 *, 0) + 0x1F60);
}
