#include "include_asm.h"

#include "rw_audio/sound.h"

extern void func_00315EE8(RwaSound *, s32);

RwaSound *func_00313F90(RwaSound *sound, s32 argument) {
    sound->driver->enable(sound, argument, 0);
    func_00315EE8(sound, 0);
    return sound;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00313FD0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314130);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003141E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314330);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314370);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003143C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003143D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314440);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314478);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314488);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003144A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_003144C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00314530);
