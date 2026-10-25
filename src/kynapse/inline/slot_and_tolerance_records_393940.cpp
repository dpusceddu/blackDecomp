#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/slot_and_tolerance_records.hpp"

// /SLUS_213.76 0x393940

void Mover::MarkDirtyNow()
{
    dirty = true;
}
