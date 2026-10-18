#include "auto/prelude.h"

extern s32 (*D_003C0E34)();

void func_00292060(void) {
    D_003C0E34();
}

s32 func_00292088(void) {
    return D_003C0E34() + 8;
}
