#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: 00155238: pool iterator and initializer lifetime context.
// Unmatched: 001553E0: inline vector and activation zero-value allocation.
// Unmatched: 001556D8: explosion helper and source matrix-reference context.
// Unmatched: 00155830: inline vector, field ordering and activation context.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00155238);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001553E0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001556D8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00155830);
#endif
