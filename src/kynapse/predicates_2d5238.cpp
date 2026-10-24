#include "include_asm.h"

// Ported from an unpublished companion project.
#include "kynapse/predicates.hpp"

// /SLUS_213.76 0x2d5238

bool IsSet50::IsSet() const { if (value != 0) return true; return false; }

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D5248);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D5328);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_002D5368);
