#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d2e48

bool Chain0C::IsSet() const
{
    if (!first)
        return false;
    if (second != 0)
        return true;
    return false;
}

// /SLUS_213.76 0x2d2e68
bool BothIds60::HasBoth() const
{
    if (first == -1)
        return false;
    if (second != -1)
        return true;
    return false;
}

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2E90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2EE8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2F00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2F40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2F48);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2F80);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2FB8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D2FD8);
