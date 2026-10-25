#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/global_accessors.hpp"

// /SLUS_213.76 0x2e9630

float FloatTable::GetValue(int index)
{
    return values[index];
}

