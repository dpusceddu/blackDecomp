// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d5198
bool BothIds28::HasBoth() const
{
    if (first == -1)
        return false;
    if (second != -1)
        return true;
    return false;
}
