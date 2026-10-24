#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/owned_arrays.hpp"

namespace Kaim {
// /SLUS_213.76 0x2f32c0

SlotOwner::~SlotOwner()
{
    for (unsigned int i = 0; i < slotCount; ++i) {
        if (slots[i])
            delete slots[i];
    }
    if (head)
        delete head;
    head = 0;
}

}  // namespace Kaim

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F3398);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F33A8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002F33C8);
