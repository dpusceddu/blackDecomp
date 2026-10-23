#include "auto/prelude.h"

extern void * func_001092F8();
extern s32 func_002886D0();
extern s32 func_0015D958();
extern void func_00108540();
extern void ** D_0040F4C4;
extern s16 func_0012E040();
extern s32 func_00168618(s32, s32, u8, void *);
extern s32 D_0040F4F4;
extern void * D_0040F4D0;

void func_0012E8B8(s32 arg0, void *arg1) {
    void *temp_2;

    temp_2 = func_001092F8();
    M2C_FIELD(arg1, void **, 0x10) = temp_2;
    func_002886D0(temp_2);
    func_0015D958(arg1 + 0x40, M2C_FIELD(M2C_FIELD(arg1, void **, 0x10), s32 *, 4), M2C_FIELD(arg1, s32 *, 0x18), M2C_FIELD(arg1, s32 *, 0x30), M2C_FIELD(arg1, s32 *, 0x1C), M2C_FIELD(arg1, s32 *, 0x34), M2C_FIELD(arg1, s32 *, 4));
    func_00108540(D_0040F4C4, 0xA, M2C_FIELD(arg1, void **, 0x10), func_0012E040(arg1));
}

void func_0012E938(void *arg0) {
    void *temp_2;

    temp_2 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), void **, 4);
    func_00168618(D_0040F4F4, M2C_FIELD(temp_2, s32 *, 0x20), M2C_FIELD(temp_2, u8 *, 0x24), D_0040F4D0 + 0x30);
}

s32 func_0012E978(void *arg0) {
    return M2C_FIELD(arg0, s8 *, 0x39) != 0;
}
