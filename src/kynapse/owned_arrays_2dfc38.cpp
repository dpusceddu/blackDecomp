#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2dfc38

PointerBankOwner::~PointerBankOwner()
{
    if (count) {
        for (int i = 0; i < count; ++i) {
            if (items[i])
                delete items[i];
        }
        memoryRelease(items);
    }
}

}  // namespace Kaim

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/owned_arrays_2dfc38", func_002DFD08);
