#include "include_asm.h"

#include "kynapse/graph/allocators.hpp"
namespace Kaim {

CBaseAllocator::~CBaseAllocator() { delete children; }
CAllocator::~CAllocator() {}
CPoolBasedAllocator::~CPoolBasedAllocator() {
    if(owner)((CAllocator*)owner)->Release((unsigned int)buffer);
    if(next)next->Remove(this);
}
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E5E58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E5FB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E6740);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E69E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E6B60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7220);
