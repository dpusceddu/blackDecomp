#include "include_asm.h"
#include "ps2/prelude.h"

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_0031E650);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_0031E9D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_0031E9D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_0031EC28);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_0031F008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_0031F210);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_0031F628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_0031FB58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_003201A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_003204A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_00320868);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_00320AD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_00321068);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_00321290);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_00321600);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_00321960);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/tu_31e650", func_00321D58);

#include "ps2/recovered_types.h"
extern s32 * func_0031E9D8(void *, s32 *, void *, s32, void *);

s32 func_00321EE0(void *arg0, s32 *arg1, s32 arg2, void *arg3, s32 arg4, s32 arg5) {
    u8 sp[8] __attribute__((aligned(16)));
    func_0031E9D8(arg0, arg1, arg3, arg2, sp);
    return *(s32 *)(sp + 0);
}
