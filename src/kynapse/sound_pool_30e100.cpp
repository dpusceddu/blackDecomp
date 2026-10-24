#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/sound_pool.hpp"

namespace Kaim {
// /SLUS_213.76 0x30e100

bool SoundPool::Restart()
{
    lastTime = gNow;
    return SoundPool::Reset();
}

}  // namespace Kaim

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E128);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E180);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E278);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E400);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E4B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E550);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E558);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E560);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0030E5A0);
