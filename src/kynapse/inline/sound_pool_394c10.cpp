#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/sound_pool.hpp"

namespace Kaim {
// /SLUS_213.76 0x394c10

ClassInfoRecord* SoundPool::GetClassInfo()
{
    return &gClassInfo2BE268;
}

}  // namespace Kaim
