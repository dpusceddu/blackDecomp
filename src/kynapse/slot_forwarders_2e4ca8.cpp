#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/slot_forwarders.hpp"

// /SLUS_213.76 0x2e4ca8

void Forwarder::RunTarget()
{
    if (target)
        target->Run();
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E4CE0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E4D18);
