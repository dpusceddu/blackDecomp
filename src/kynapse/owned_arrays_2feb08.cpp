// Ported from the companion project (an unpublished companion project).
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2feb08
BlockTable::~BlockTable()
{
    if (blocks) {
        for (int i = 0; i < count; ++i)
            memoryRelease(blocks[i]);
        memoryRelease(blocks);
    }
}

}  // namespace Kaim
