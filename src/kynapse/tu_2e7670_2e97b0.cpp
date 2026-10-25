#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/parameters.hpp"
#endif

#ifdef NON_MATCHING
// Unmatched: rank-pointer helper register scheduling.
bool ParameterViews::RaiseIndex(int index,IndexUser *user) {
    int slot=user->GetIndex();
    if(index>=0 && (unsigned int)index<countB && (unsigned int)slot<GetSlotOwner()->indexCount) {
        float *rank=indexTables[slot].values+index;
        if(*rank+b2c[index]<gSavedFloat){*rank=gSavedFloat;return true;}
    }
    return false;
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2e7670_2e97b0", func_002E97B0);
#endif
