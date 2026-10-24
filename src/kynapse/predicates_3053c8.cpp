// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x3053c8
bool Flags5F550::Get() const
{
    if (!blocked && enabled)
        return value;
    return false;
}
