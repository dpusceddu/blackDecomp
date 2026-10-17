// Ported from the companion project (an unpublished companion project).
#include "kynapse/sound_pool.hpp"

namespace Kaim {
// /SLUS_213.76 0x30e100
bool SoundPool::Restart()
{
    lastTime = gNow;
    return SoundPool::Reset();
}

}  // namespace Kaim
