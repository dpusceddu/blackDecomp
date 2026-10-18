#include "kynapse/pair_owner.hpp"

#ifdef NONMATCHING
// Unmatched: deleting-destructor tail allocates v0/v1 in the opposite order.
PairOwner::~PairOwner()
{
    delete[] elements;
    tag = 0;
    elements = 0;
    field18 = 0;
    field1c = 0;
    field20 = 0;
    field24 = 0;
    field28 = 0;
    field2c = 0;
    field34 = 0;
    field38 = 0;
    field3c = 0;
    field40 = 0;
    field44 = 0;
    if (--gPairOwnerCount == 0) {
        if (gPairFlagsTable) {
            memoryRelease(gPairFlagsTable);
            gPairFlagsTable = 0;
        }
        if (gPairSecondTable) {
            memoryRelease(gPairSecondTable);
            gPairSecondTable = 0;
        }
        if (gPairThirdTable) {
            memoryRelease(gPairThirdTable);
            gPairThirdTable = 0;
        }
        if (gPairValuesTable) {
            memoryRelease(gPairValuesTable);
            gPairValuesTable = 0;
        }
    }
    Entity_ApplyD(gEngine, (int)PairOwnerOnRemoved, (int)this);
}
#endif
