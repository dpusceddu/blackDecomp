// Ported from the companion project (an unpublished companion project).
#include "kynapse/leaves2.hpp"

// /SLUS_213.76 0x30d130
bool Kaim_PairIdsValid()
{
    if (gIdH == -1 || gIdI == -1)
        return false;
    return true;
}
