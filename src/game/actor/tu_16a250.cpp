#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: 0x16A250 original byte predicate branch and shared return-tail scheduling.
// Unmatched: 0x16A2F8 trigger/policy control flow and repeated virtual-call lifetimes.
// Unmatched: 0x16A4C0 near-point byte helper, affine matrix and Y-offset VU allocation.
// Unmatched: 0x16A5E8 AABB short-circuit accumulator and VU lvalue allocation.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A250);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A2F8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0016A5E8);
#endif

#ifdef NON_MATCHING
// Unmatched: 0x16A2F8 byte predicate, trigger/policy control flow and repeated virtual-call lifetimes.
#endif
