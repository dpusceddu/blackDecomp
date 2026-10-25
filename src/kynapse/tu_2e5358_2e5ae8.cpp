#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/allocators.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CPoolBasedAllocator::CPoolBasedAllocator(int n,CAllocator *parent,unsigned int childrenCount):CAllocator(childrenCount) {
    next=parent;bytes=AlignedSize(n);buffer=parent->FindAny(bytes,this);
    if(!buffer)bytes=0;used=0;unused=0;
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E5AE8);
#endif
