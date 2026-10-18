#include "auto/prelude.h"

extern void * func_001092F8();
extern s32 func_002886D0();
extern s32 func_0015D958();
extern void func_00108540();
extern void ** D_0040F4C4;
extern s16 func_0012E040();

void func_0012E8B8(s32 arg0, void *arg1) {
    void *temp_2;

    temp_2 = func_001092F8();
    M2C_FIELD(arg1, void **, 0x10) = temp_2;
    func_002886D0(temp_2);
    func_0015D958(arg1 + 0x40, M2C_FIELD(M2C_FIELD(arg1, void **, 0x10), s32 *, 4), M2C_FIELD(arg1, s32 *, 0x18), M2C_FIELD(arg1, s32 *, 0x30), M2C_FIELD(arg1, s32 *, 0x1C), M2C_FIELD(arg1, s32 *, 0x34), M2C_FIELD(arg1, s32 *, 4));
    func_00108540(D_0040F4C4, 0xA, M2C_FIELD(arg1, void **, 0x10), func_0012E040(arg1));
}
