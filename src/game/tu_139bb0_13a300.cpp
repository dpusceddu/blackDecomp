#include "include_asm.h"

#ifdef NON_MATCHING
#include "game/classes/UnknownVtable_003DC5F8.hpp"
#include "ps2/matrix.hpp"

// Unmatched: 0013A300 state update retains scalar allocation and counter-bank differences.
// Unmatched: 0013A6E8 transform update needs verified matrix copy/compound operators and VU trig helpers.
// Unmatched: 0013B4C0 matrix return needs the original C++ matrix copy constructor/temporary stores.
// Unmatched: 0013B628 draw update retains matrix copy and short iterator allocation differences.
// Unmatched: 0013BB78 burn damage retains vector spill/notification control-flow differences.
// Unmatched: 0013BDF8 collision damage needs original normalization temporary lifetimes.
// Unmatched: 0013C3E8 explosive damage retains component accessor and argument allocation differences.
// Unmatched: 0013C528 directional damage retains eight component-address/scheduling differences.
// Unmatched: 00383920 kind setter is instruction-exact but leaves an unexplained 12-byte retail gap.
#else
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013A300);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013A6E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013B4C0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013B628);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013BB78);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013BDF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013C3E8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013C528);
#endif

INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013A640);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013B4A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013B9A0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013B9D0);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013BA00);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013BA40);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013BAC8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013BAF8);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013BB38);
INCLUDE_ASM("asm/SLUS_213.76/nonmatchings", func_0013C1B0);
