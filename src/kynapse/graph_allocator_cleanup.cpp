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
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E6CF0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E6D90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E6DD8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E6E60);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E6F90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E6FB0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7008);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7028);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7088);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7090);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E70F0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7158);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E71E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E7220);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002E72D0);
