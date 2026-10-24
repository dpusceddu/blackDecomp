// Ported from an unpublished companion project.
#include "kynapse/callbacks.hpp"

// /SLUS_213.76 0x2f0da8
bool Kaim_AllRegisteredIdsValid()
{
    if (gId0 == -1
        || gId1 == -1
        || gId2 == -1
        || gId3 == -1
        || gId4 == -1
        || gId5 == -1
        || gId6 == -1
        || gId7 == -1
        || gId8 == -1
        || gId9 == -1
        || gId10 == -1
        || gId11 == -1
        || gId12 == -1
        || gId13 == -1
        || gId14 == -1
        || gId15 == -1)
        return false;
    return true;
}
