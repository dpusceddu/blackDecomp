#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2fd800

ShortBlockTable::~ShortBlockTable()
{
    for (int i = 0; i < count; ++i) {
        if (blocks[i])
            memoryRelease(blocks[i]);
    }
    memoryRelease(blocks);
    memoryRelease(extra);
}

}  // namespace Kaim
