#include "auto/prelude.h"

extern s32 func_0020DF68();
extern M2C_UNK D_003FC0C8;
extern s32 func_00216B00();
extern s32 func_0020DF90();
extern s32 D_003BE8B8;

s32 func_00216A98(s32 arg0) {
    func_0020DF68(arg0, (s32) &D_003FC0C8, (s32) func_00216B00);
    return 1;
}

s32 func_00216AC8(s32 arg0) {
    func_0020DF90(arg0, (s32) &D_003FC0C8);
    return 1;
}

void func_00216AF0(s32 arg0) {
    D_003BE8B8 = arg0;
}
