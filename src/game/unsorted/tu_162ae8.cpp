#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: 0x162AE8 inventory-loop allocation and scheduling remain after native command and narrowed state setter recovery.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00162AE8);
#endif
