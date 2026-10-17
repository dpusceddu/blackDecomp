// Ported from the companion project (an unpublished companion project).
#include "kynapse/accessors.hpp"

// /SLUS_213.76 0x2e10b8
// Unmatched: identical operations; the original lays the negative exit out first (11 bytes).
// Doubles the growth counter unless it has gone negative.
int GrowthCounter_Double()
{
    int value = gGrowthCounter;
    if (value & 0x80000000)
        return 0;
    value = value + value;
    gGrowthCounter = value;
    return value;
}
