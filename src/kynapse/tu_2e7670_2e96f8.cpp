#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/parameters.hpp"
#endif

#ifdef NON_MATCHING
// Unmatched: rank-pointer helper register scheduling.
bool ParameterTables::Raise(int index,SlotUser *user) {
    int slot=user->GetIndex();
    if(index>=0 && (unsigned int)index<countB && (unsigned int)slot<GetSlotOwner()->slotCount) {
        float *rank=sets[slot].ranks+index;
        if(*rank+b2c[index]<gSavedFloat){*rank=gSavedFloat;return true;}
    }
    return false;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2e7670_2e96f8", func_002E96F8);
#endif
