#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/slot_and_tolerance_records.hpp"

// /SLUS_213.76 0x3053f0

void Kaim_ApplyToTarget(int argument, Target* target)
{
    if (target)
        target->Apply(argument);
}

// /SLUS_213.76 0x305428
void Mover::MarkDirty(int)
{
    dirty = true;
}

