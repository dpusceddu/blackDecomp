/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CPATHOBJECTMANAGER_H
#define RECOVERED_CPATHOBJECTMANAGER_H
#include "ps2/prelude.h"

typedef struct Recovered_CPathObjectManager {
    u32 field_0; /* PS2 +0x0 */
    void * field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    void * field_C; /* PS2 +0xC */
    s32 field_10; /* PS2 +0x10 */
    void * field_14; /* PS2 +0x14 */
    s32 field_18; /* PS2 +0x18 */
} Recovered_CPathObjectManager;
typedef char assert_Recovered_CPathObjectManager_0[(((int)&((Recovered_CPathObjectManager *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_CPathObjectManager_4[(((int)&((Recovered_CPathObjectManager *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_CPathObjectManager_8[(((int)&((Recovered_CPathObjectManager *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_CPathObjectManager_C[(((int)&((Recovered_CPathObjectManager *)0)->field_C) == 12) ? 1 : -1];
typedef char assert_Recovered_CPathObjectManager_10[(((int)&((Recovered_CPathObjectManager *)0)->field_10) == 16) ? 1 : -1];
typedef char assert_Recovered_CPathObjectManager_14[(((int)&((Recovered_CPathObjectManager *)0)->field_14) == 20) ? 1 : -1];
typedef char assert_Recovered_CPathObjectManager_18[(((int)&((Recovered_CPathObjectManager *)0)->field_18) == 24) ? 1 : -1];
#endif
