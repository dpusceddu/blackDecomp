#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2f2578

PoolArray::~PoolArray()
{
    for (unsigned int i = 0; i < count; ++i) {
        if (items[i])
            delete items[i];
        items[i] = 0;
    }
    memoryRelease(items);
    items = 0;
    ReleaseSharedPool();
}

}  // namespace Kaim

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F2660);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F28F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F2BF8);
