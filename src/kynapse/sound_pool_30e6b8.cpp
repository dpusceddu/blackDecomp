#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/sound_pool.hpp"

namespace Kaim {
// /SLUS_213.76 0x30e6b8

int* SoundPool::GetCounter(unsigned int mask)
{
    switch (mask) {
    case 1:
        return &counterKind1;
    case 2:
        return &counterKind2;
    case 4:
        return &counterKind4;
    case 0x20:
        return &counterKind32;
    case 8:
        return &counterKind8;
    case 0x10:
        return &counterKind16;
    case 0x40:
        return &counterKind64;
    }
    return 0;
}

}  // namespace Kaim
