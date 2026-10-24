/* PS2 access view (hand-maintained). UNVERIFIED access view; allocation size unknown. */
#ifndef RECOVERED_PATHMANAGER_H
#define RECOVERED_PATHMANAGER_H
#include "ps2/prelude.h"

typedef struct Recovered_PathManager {
    u32 field_0; /* PS2 +0x0 */
    s32 field_4; /* PS2 +0x4 */
    s32 field_8; /* PS2 +0x8 */
    s32 field_C; /* PS2 +0xC */
} Recovered_PathManager;
typedef char assert_Recovered_PathManager_0[(((int)&((Recovered_PathManager *)0)->field_0) == 0) ? 1 : -1];
typedef char assert_Recovered_PathManager_4[(((int)&((Recovered_PathManager *)0)->field_4) == 4) ? 1 : -1];
typedef char assert_Recovered_PathManager_8[(((int)&((Recovered_PathManager *)0)->field_8) == 8) ? 1 : -1];
typedef char assert_Recovered_PathManager_C[(((int)&((Recovered_PathManager *)0)->field_C) == 12) ? 1 : -1];
#endif
