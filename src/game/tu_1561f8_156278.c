#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_0015D210();
extern void ** D_0040F4E0;
extern s32 func_0015D228();
extern s32 func_0015D060();
extern s32 func_0020BC00();
extern s32 D_0040F544;
extern s32 func_00209EC8();
extern s32 func_0027C278();
extern M2C_UNK D_003F4C40;
extern M2C_UNK D_003BCEB4;

s32 func_00156278(void *arg0, s32 arg1, s8 arg2, u8 *arg3) {
    s32 temp_16;

    M2C_FIELD(arg0, s32 *, 0xF0) = arg1;
    M2C_FIELD(arg0, s8 *, 0) = arg2;
    M2C_FIELD(arg0, s32 *, 0xFC) = (s32) (arg1 + 0x280);
    M2C_FIELD(arg0, s32 *, 0xD8) = 0;
    M2C_FIELD(arg0, s32 *, 0xDC) = 0;
    M2C_FIELD(arg0, s32 *, 0xE0) = 0;
    M2C_FIELD(arg0, s8 *, 0x105) = 0;
    M2C_FIELD(arg0, s8 *, 0x106) = 0;
    M2C_FIELD(arg0, s8 *, 0x107) = 0;
    M2C_FIELD(arg0, s8 *, 0x108) = 0;
    M2C_FIELD(arg0, s8 *, 0x109) = 0;
    M2C_FIELD(arg0, s8 *, 0x3C) = 0;
    M2C_FIELD(arg0, s8 *, 0x10A) = 0;
    M2C_FIELD(arg0, s8 *, 0x10B) = 0;
    M2C_FIELD(arg0, s8 *, 0x10C) = 0;
    M2C_FIELD(arg0, s8 *, 0x10D) = 0;
    M2C_FIELD(arg0, s8 *, 0x100) = 0;
    M2C_FIELD(arg0, s8 *, 0x101) = 0;
    M2C_FIELD(arg0, s8 *, 0x102) = 0;
    M2C_FIELD(arg0, s8 *, 0x104) = 0;
    M2C_FIELD(arg0, s8 *, 0x103) = 0;
    M2C_FIELD(arg0, s32 *, 0xE8) = func_0015D210(D_0040F4E0, arg2);
    M2C_FIELD(arg0, s32 *, 0xEC) = func_0015D228(D_0040F4E0, arg2);
    func_0015D060(D_0040F4E0, arg0, arg3);
    M2C_FIELD(arg0, s32 *, 4) = 0;
    temp_16 = func_0020BC00(D_0040F544, 2);
    func_00209EC8(temp_16, func_0027C278(&D_003F4C40), &D_003BCEB4);
    return 1;
}
