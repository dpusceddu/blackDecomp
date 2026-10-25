#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_001D5DA8(s32, f32);
extern void * D_0040F510;
extern s32 D_0040F0E0;
extern s32 func_001D5D40(s32, f32);
extern s32 func_00283200(s32, u32);
extern s32 func_00211F10(s32);

s32 func_00211C90(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    func_001D5DA8((s32) D_0040F510, M2C_FIELD(D_0040F0E0, f32 *, 0x2015C));
    func_001D5D40((s32) D_0040F510, M2C_FIELD(D_0040F0E0, f32 *, 0x20160));
    return func_00283200((s32) D_0040F510, func_00211F10(M2C_FIELD(D_0040F0E0, s32 *, 0x20154)));
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_211c90", func_00211D10);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_211c90", func_00211D78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/game/unsorted/tu_2094b0_211c90", func_00211DF0);
