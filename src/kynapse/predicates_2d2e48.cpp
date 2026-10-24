// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d2e48
bool Chain0C::IsSet() const
{
    if (!first)
        return false;
    if (second != 0)
        return true;
    return false;
}

// /SLUS_213.76 0x2d2e68
bool BothIds60::HasBoth() const
{
    if (first == -1)
        return false;
    if (second != -1)
        return true;
    return false;
}
