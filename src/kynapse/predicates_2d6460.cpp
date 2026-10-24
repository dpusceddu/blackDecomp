#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d6460

bool HasLink::IsSet() const
{
    if (!link)
        return false;
    if (link->value != 0)
        return true;
    return false;
}
