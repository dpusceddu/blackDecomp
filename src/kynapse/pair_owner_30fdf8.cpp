// Ported from the companion project (an unpublished companion project).
#include "kynapse/pair_owner.hpp"

namespace Kaim {
// /SLUS_213.76 0x30fdf8
PairOwner::PairOwner(int value) : PairOwnerBase(value)
{
    high = 0.5f;
    low = 0.1f;
    ++gPairOwnerCount;
}

}  // namespace Kaim
