#include "include_asm.h"

#ifdef NON_MATCHING
// Unmatched: 51/425 instructions differ in scalar views, shared point tails and VU allocation; 1704-byte span is preserved.
// Synthetic finite-input checks cover feature memory and preserved registers; gameplay, VU scratch state and W are unverified.
// Recorded replay: 9/54 pass; 45 differ in VU outputs, with 64% original block coverage. This remains a draft.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings/physics/tu_33f400", func_0033F400);
#endif
