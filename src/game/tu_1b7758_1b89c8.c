#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: 0x1b89c8: 0x110-byte simulation records; VU I-register rotation and stack matrices.
// Unmatched: 0x1b9b58: twenty-fragment geometry/UV tables, 128-bit values and 0x3b0-byte frame.
// Unmatched: 0x1bb190: sixteen-point fracture workspaces, vector-valued returns and shared edge tables.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B89C8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B9B58);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BB190);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B90D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B9198);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B96B8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001B9A40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BAB90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BAD90);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001BAF90);
