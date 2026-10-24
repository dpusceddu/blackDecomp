/* Partial view of a PS2 type (hand-maintained; see README.md in this directory). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CGRAPHMANAGER_H
#define RECOVERED_CGRAPHMANAGER_H
#include "ps2/prelude.h"

typedef struct Recovered_CGraphManager {
    u32 field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
    u8 field_10; /* PS2 +0x10 */
} Recovered_CGraphManager;
typedef char assert_Recovered_CGraphManager_0[(((int)&((Recovered_CGraphManager *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_CGraphManager_4[(((int)&((Recovered_CGraphManager *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_CGraphManager_8[(((int)&((Recovered_CGraphManager *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_CGraphManager_C[(((int)&((Recovered_CGraphManager *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_CGraphManager_10[(((int)&((Recovered_CGraphManager *)0)->field_10) == 16) ? 1 : -1];
#endif
