/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_FRONTENDRESOURCETABLE_H
#define RECOVERED_FRONTENDRESOURCETABLE_H
#include "ps2/prelude.h"

typedef struct Recovered_FrontendResourceTable {
    u8 opaque_0[940];
    void * field_3AC; /* PS2 +0x3AC */
    u8 opaque_3B0[4];
    u32 field_3B4; /* PS2 +0x3B4 */
    u8 field_3B8; /* PS2 +0x3B8 */
} Recovered_FrontendResourceTable;
typedef char assert_Recovered_FrontendResourceTable_3AC[(((int)&((Recovered_FrontendResourceTable *)0)->field_3AC) == 940) ? 1 : -1];
typedef char assert_Recovered_FrontendResourceTable_3B4[(((int)&((Recovered_FrontendResourceTable *)0)->field_3B4) == 948) ? 1 : -1];
typedef char assert_Recovered_FrontendResourceTable_3B8[(((int)&((Recovered_FrontendResourceTable *)0)->field_3B8) == 952) ? 1 : -1];
#endif
