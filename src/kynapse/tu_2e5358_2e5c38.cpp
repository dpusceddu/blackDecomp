#include "include_asm.h"
#include "ps2/prelude.h"
#ifdef NON_MATCHING
#include "kynapse/graph/allocators.hpp"
#endif

#ifdef NON_MATCHING
namespace Kaim {
// Unmatched: container temporaries, cleanup visibility or register scheduling.
CPoolBasedAllocator::CPoolBasedAllocator(void *p,int n,CAllocator *parent,unsigned int childrenCount):CAllocator(childrenCount) {
    next=parent;buffer=p;bytes=AlignedSize(n);used=0;unused=0;if(parent)parent->Add(this);
}
}
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/kynapse/tu_2e5358_2e5c38", func_002E5C38);
#endif
