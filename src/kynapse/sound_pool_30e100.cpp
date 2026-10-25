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

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/sound_pool_30e100", func_0030E180);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/sound_pool_30e100", func_0030E320);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/sound_pool_30e100", func_0030E5A0);
