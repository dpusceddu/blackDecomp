#include "include_asm.h"

#ifdef NON_MATCHING
#include "physics/collision_work.h"

// Unmatched: 0032FBC0 compound moment summation; VU operand allocation and prologue scheduling differ.
// Unmatched: 0032FCA0 primitive/compound/bounds moment tensor; homogeneous matrix temporary lowering differs.
// Unmatched: 00330CF8 sphere, capsule and rounded-box inertia; VU lane updates and float scheduling differ.
// Unmatched: 00331008 mass definition and principal-axis decomposition; centered tensor and matrix temporary lowering differs.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032FBC0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0032FCA0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00330CF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_00331008);
#endif
