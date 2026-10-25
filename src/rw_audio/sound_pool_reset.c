#include "include_asm.h"

#include "rw_audio/sound.h"

extern void func_00317FC0(void *);
extern u8 D_004563A8[];
extern u32 D_0040E188;

void func_00316218(void) {
    func_00317FC0(D_004563A8);
    D_0040E188=0;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/sound_pool_reset", func_00316240);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/sound_pool_reset", func_003162D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/sound_pool_reset", func_003163F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/sound_pool_reset", func_00316400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/sound_pool_reset", func_00316430);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/rw_audio/sound_pool_reset", func_00316438);
