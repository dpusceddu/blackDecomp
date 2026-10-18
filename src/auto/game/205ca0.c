#include "auto/prelude.h"

extern s32 func_00204F30();
extern s32 func_00206A58();
extern s32 func_00206B88();
extern void * D_0040F0E0;

s32 func_00205CA0(void *arg0) {
    func_00204F30();
    func_00206A58(arg0 + 0x60);
    func_00206B88(arg0 + 0x88);
    M2C_FIELD(D_0040F0E0, u8 *, 0x2020C) = (u8) M2C_FIELD(((M2C_FIELD(arg0, s8 *, 0xC9) * 0x24) + M2C_FIELD(M2C_FIELD(D_0040F0E0, void **, 0x2106C), s32 *, 4)), u8 *, 0x10);
    M2C_FIELD(D_0040F0E0, s8 *, 0x2020D) = (s8) (M2C_FIELD(arg0, u8 *, 0xCA) + 1);
    M2C_FIELD(D_0040F0E0, s8 *, 0x2020E) = 1;
    M2C_FIELD(arg0, s8 *, 0xC8) = 1;
    M2C_FIELD(arg0, s32 *, 0xCC) = 2;
    M2C_FIELD(arg0, s8 *, 0xD0) = 0;
    return 1;
}
