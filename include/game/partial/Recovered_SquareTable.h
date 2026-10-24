/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_SQUARETABLE_H
#define RECOVERED_SQUARETABLE_H
#include "ps2/prelude.h"

typedef struct Recovered_SquareTable {
    u32 field_0; /* PS2 +0x0 */
    u32 field_4; /* PS2 +0x4 */
    u32 field_8; /* PS2 +0x8 */
    u32 field_C; /* PS2 +0xC */
    u32 field_10; /* PS2 +0x10 */
    u32 field_14; /* PS2 +0x14 */
} Recovered_SquareTable;
typedef char assert_Recovered_SquareTable_0[(((int)&((Recovered_SquareTable *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_SquareTable_4[(((int)&((Recovered_SquareTable *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_SquareTable_8[(((int)&((Recovered_SquareTable *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_SquareTable_C[(((int)&((Recovered_SquareTable *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_SquareTable_10[(((int)&((Recovered_SquareTable *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_SquareTable_14[(((int)&((Recovered_SquareTable *)0)->field_14) == 20) ? 1 : -1];
#endif
