#include "auto/prelude.h"

extern s32 func_0032E1B0(s32, void *);
extern s32 func_00100290(s32, s32, M2C_UNK);

void func_0025CE28(void *arg0) {
    M2C_FIELD(arg0, s32 *, 0x8B04) = -1;
}

void func_0025CE40(s32 *arg0, void *arg1) {
    if (func_0032E1B0(*arg0, M2C_FIELD(arg1, void **, 0x34)) != 0) {
        func_00100290(*arg0, M2C_FIELD(M2C_FIELD(arg1, void **, 0x34), s32 *, 0xC), 1);
    }
}
