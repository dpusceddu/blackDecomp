#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d70c0

bool Chain50::IsSet() const
{
    if (!first)
        return false;
    if (second != 0)
        return true;
    return false;
}

// /SLUS_213.76 0x2d70e0
bool Either54::IsSet() const
{
    if (!a && !b)
        return false;
    if (c != 0)
        return true;
    return false;
}

// /SLUS_213.76 0x2d7108
bool HasId68::HasId() const { if (id != -1) return true; return false; }

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D7118);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D71E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D7200);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D7220);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D7240);
