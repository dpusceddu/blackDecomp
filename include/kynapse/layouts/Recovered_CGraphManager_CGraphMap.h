/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_CGRAPHMANAGER_CGRAPHMAP_H
#define RECOVERED_CGRAPHMANAGER_CGRAPHMAP_H
#include "ps2/prelude.h"

typedef struct Recovered_CGraphManager_CGraphMap {
    u32 field_0; /* PS2 +0x0 */
    u8 opaque_4[127];
    u8 field_83; /* PS2 +0x83 */
    u32 field_84; /* PS2 +0x84 */
    u8 field_88; /* PS2 +0x88 */
    u8 opaque_89[131];
    u32 field_10C; /* PS2 +0x10C */
} Recovered_CGraphManager_CGraphMap;
typedef char assert_Recovered_CGraphManager_CGraphMap_0[(((int)&((Recovered_CGraphManager_CGraphMap *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_CGraphManager_CGraphMap_83[(((int)&((Recovered_CGraphManager_CGraphMap *)0)->field_83) == 131) ? 1 : -1];
typedef char assert_Recovered_CGraphManager_CGraphMap_84[(((int)&((Recovered_CGraphManager_CGraphMap *)0)->field_84) == 132) ? 1 : -1];
typedef char assert_Recovered_CGraphManager_CGraphMap_88[(((int)&((Recovered_CGraphManager_CGraphMap *)0)->field_88) == 136) ? 1 : -1];
typedef char assert_Recovered_CGraphManager_CGraphMap_10C[(((int)&((Recovered_CGraphManager_CGraphMap *)0)->field_10C) == 268) ? 1 : -1];
#endif
