#include "include_asm.h"

#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 D_003BD3F8;
extern s32 D_003BD3FC;
extern s32 D_003BD400;
extern s32 D_003BD404;
extern s32 D_003BD408;
extern s32 D_003BD40C;
extern s32 D_003BD410;

s32 func_001E3018(void *arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 0:
        return D_003BD3F8;
    case 1:
        return D_003BD3FC;
    case 2:
        return D_003BD400;
    case 4:
        return D_003BD404;
    case 8:
        return D_003BD408;
    case 16:
        return D_003BD40C;
    case 32:
        return D_003BD410;
    default:
        return 0;
    }
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001E3098);
