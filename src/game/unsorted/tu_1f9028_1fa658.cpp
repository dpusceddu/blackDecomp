#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: notification update needs mixed scalar/vector aggregate and tween helper recovery.
// Unmatched: state transitions need inline copy ordering and register lifetime recovery.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_001FA658);
#endif
