#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/lookups.hpp"

namespace Kaim {
// /SLUS_213.76 0x2e1b08

void ComponentSweep::Sweep()
{
    for (int i = 0; i < primaryCount; ++i)
        primary[i]->Slot3();
    for (int i = 0; i < secondaryCount; ++i)
        secondary[i]->Slot3();
}

}  // namespace Kaim

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1BC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1C58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E1D10);
