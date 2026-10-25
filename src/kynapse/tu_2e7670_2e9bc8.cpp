#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/parameters.hpp"
#endif

#ifdef NON_MATCHING
// Unmatched: float return register allocation.
float ParameterTables::Remaining(int index)
{
    if (index < 0 || (unsigned int)index > countA - 1)
        return kDefaultFloat;
    if (threshold <= kDefaultFloat)
        return 3.402823466e38f;
    float now = gFloatHook ? gFloatHook() : kDefaultFloat;
    float left = threshold - now;
    if (left < kDefaultFloat)
        return kDefaultFloat;
    float room = a20[index] - a40[index];
    if (room < kDefaultFloat)
        return kDefaultFloat;
    if (!(left < room))
        return room;
    return left;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2e7670_2e9bc8", func_002E9BC8);
#endif
