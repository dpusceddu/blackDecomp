#include "auto/prelude.h"

extern s32 func_00316400(s32, M2C_UNK *);
extern M2C_UNK D_004092D0;
extern s32 func_00312C70(s32);
extern s32 func_00328E60();
extern s32 func_003287F0();
extern s32 func_003242B0();
extern s32 func_00328EB8();

void func_00329078(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x29) & 1) && (func_00316400(M2C_FIELD(arg0, s32 *, 0x14), &D_004092D0) != 0)) {
        func_00312C70(M2C_FIELD(arg0, s32 *, 0x4C));
        return;
    }
    func_00328E60(M2C_FIELD(arg0, s32 *, 0x4C));
}

s32 func_003290D8(s32 arg0) {
    if (func_003287F0(arg0, M2C_FIELD(arg0, s32 *, 0x58)) != 0) {
        return M2C_FIELD(arg0, s32 *, 0x4C);
    }
    return 0;
}

void func_00329110(void *arg0) {
    if ((M2C_FIELD(arg0, u8 *, 0x29) & 1) && (func_00316400(M2C_FIELD(arg0, s32 *, 0x14), &D_004092D0) != 0)) {
        func_00312C70(M2C_FIELD(arg0, s32 *, 0x4C));
        return;
    }
    func_00328E60(M2C_FIELD(arg0, s32 *, 0x4C));
}

void func_00329170(s32 arg0, s32 arg1, M2C_UNK *arg2, s32 arg3) {
    func_003242B0(func_00328EB8() + arg1, arg2, (arg3 + 0x3F) & 0xFFFFFFC0, 7, 0, NULL, 0, 0);
}
