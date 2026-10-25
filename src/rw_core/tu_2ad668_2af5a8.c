#include "include_asm.h"
#include "ps2/prelude.h"

#include "ps2/recovered_types.h"
extern s32 func_002CFAC0(void *, u32, u32, u32, u32, s32);
extern s32 D_003C3370;

s32 func_002AF5A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return func_002CFAC0(&D_003C3370, (u32) arg0, (u32) arg1, (u32) arg2, (u32) arg3, arg4);
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ad668_2af5a8", func_002AF5F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ad668_2af5a8", func_002AF608);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ad668_2af5a8", func_002AF6A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_core/tu_2ad668_2af5a8", func_002AF6F0);
