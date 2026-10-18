#include "auto/prelude.h"

extern s32 func_003242B0();
extern s32 func_00328EB8();

void func_00329170(s32 arg0, s32 arg1, M2C_UNK *arg2, s32 arg3) {
    func_003242B0(func_00328EB8() + arg1, arg2, (arg3 + 0x3F) & 0xFFFFFFC0, 7, 0, NULL, 0, 0);
}
