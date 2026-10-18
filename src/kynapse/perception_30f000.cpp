#include "kynapse/perception.hpp"

#ifdef NONMATCHING
// Unmatched: record assignment and destructor scheduling differ.
void Perception::Reset()
{
    unsigned int pairs = (unsigned int)(gWorld->maxEntities * (gWorld->maxEntities - 1)) >> 1;
    if ((int)pairs > 0) {
        memset(gPairFlags, 0, pairs);
        memset(gPairExpiry, 0, pairs << 2);
        memset(gPairLineExpiry, 0, pairs << 2);
        memset(gPairDistances, 0, pairs << 2);
    }
    PerceptionRecord empty;
    for (unsigned int i = 0; i < (unsigned int)gWorld->maxEntities; ++i)
        records[i] = empty;
    pendingCone = true;
    pendingGroup = true;
    pendingLine = true;
}
#endif
