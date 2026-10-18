#include "auto/prelude.h"

extern s32 D_003C0E04;
extern s32 D_003BD9D8;
extern s32 D_003BD9D0;

void func_001EB490(void) {
    if ((u32) (D_003C0E04 - D_003BD9D8) >= 2U) {
        D_003BD9D0 = D_003C0E04;
    }
    D_003BD9D8 = D_003C0E04;
}
