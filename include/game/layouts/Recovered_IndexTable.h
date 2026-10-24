/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_INDEXTABLE_H
#define RECOVERED_INDEXTABLE_H
#include "ps2/prelude.h"

typedef struct Recovered_IndexTable {
    u32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
} Recovered_IndexTable;
typedef char assert_Recovered_IndexTable_0[(((int)&((Recovered_IndexTable *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_IndexTable_4[(((int)&((Recovered_IndexTable *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_IndexTable_8[(((int)&((Recovered_IndexTable *)0)->field_8) == 8) ? 1 : -1];
#endif
