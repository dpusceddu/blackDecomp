#include "include_asm.h"
#include "ps2/prelude.h"

extern s32 func_00204F30();
extern s32 func_00206130();
extern s32 func_00206248();
extern s32 func_00103800();
extern s32 * D_0040F0E0;

s32 func_00205878(s32 arg0, s32 arg1) {
    func_00204F30(arg0);
    M2C_FIELD(arg0, s32 *, 0xB8) = arg1;
    func_00206130(arg0 + 0x60, 1, 0x1E, 0x1E);
    func_00206248(arg0 + 0x7C, 1, 0x1E, 0x1E);
    func_00103800((s32) D_0040F0E0, 1);
    M2C_FIELD(arg0, s8 *, 0xBC) = 0;
    return 1;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002058F0);
